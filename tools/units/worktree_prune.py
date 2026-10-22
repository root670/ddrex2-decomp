#!/usr/bin/env python3
"""worktree_prune.py -- retire agent worktrees whose source already reached master.

Parallel unit work lives in git worktrees under ``.git/agents/<name>`` on branches
``wt-<name>``.  Once the controller has cherry-picked an agent's source, the worktree is dead
weight: it keeps a full checkout, a branch, and a row in ``git worktree list``.  This tool
decides, for each registered worktree in that directory, whether it can go.

The verdict is **KEEP** unless all of the following hold, in which case it is **REMOVE**:

* the worktree is not live -- no ``.live`` marker in it, and nothing in it was modified within
  ``--age-minutes`` (default 30), because an agent may still be running in it;
* git does not report it locked;
* it has no uncommitted changes under ``src/`` (tracked, staged or untracked) -- that is work
  nothing has integrated yet, and it must never be thrown away;
* its ``src/`` matches master -- compared as a working tree when the checkout is present, so
  uncommitted changes are part of the comparison;
* its branch has no commits reachable from nowhere but master that touch ``src/``.  A branch
  commit already merged is not a reason to keep the worktree; a commit whose source has not
  reached master is, even if a later branch commit reverted the file.

REMOVE archives ``git diff <main-branch>`` to ``.git/agent-rows/<name>.diff`` first, so the
worktree's committed and uncommitted state survives as a patch, and only then runs
``git worktree remove --force`` and deletes the ``wt-`` branch.  Directories under
``.git/agents`` that git does not list as worktrees are ignored, never deleted.

The tool refuses to run at all when the main checkout has changes under ``src/``: comparing
against a half-edited master would call an unmerged worktree integrated.  Nothing is removed
when that check fails.

Usage::

    python3 tools/units/worktree_prune.py                    # prune, print a summary
    python3 tools/units/worktree_prune.py --dry-run          # verdicts only, change nothing
    python3 tools/units/worktree_prune.py --age-minutes 5    # a shorter live window

Run it from inside the repository; the repository containing the current directory is the
one pruned.  Exit codes: 0 nothing to do or every removal succeeded, 1 a removal or archive
failed, 2 unusable invocation or a dirty main checkout.
"""

from __future__ import annotations

import argparse
import os
import subprocess
import sys
import time

AGENTS = os.path.join(".git", "agents")
ROWS = os.path.join(".git", "agent-rows")
LIVE_MARKER = ".live"
BRANCH_PREFIX = "wt-"
SRC = "src"

REMOVE = "REMOVE"
KEEP = "KEEP"
IGNORE = "IGNORE"


class Unusable(Exception):
    """The repository, invocation or git state cannot be used; nothing was changed."""


def git(args, cwd):
    result = subprocess.run(["git", *args], cwd=cwd, capture_output=True, text=True)
    if result.returncode != 0:
        message = result.stderr.strip() or result.stdout.strip() or "git failed"
        raise Unusable(f"git {' '.join(args)}: {message}")
    return result.stdout


def git_status(args, cwd) -> int:
    return subprocess.run(["git", *args], cwd=cwd, capture_output=True, text=True).returncode


class Worktree:
    """One block of ``git worktree list --porcelain``."""

    def __init__(self, path, head, branch, locked):
        self.path = path
        self.head = head
        self.branch = branch          # short branch name, or None when detached
        self.locked = locked

    @property
    def name(self):
        return os.path.basename(self.path.rstrip(os.sep))


def parse_worktrees(text, main_root):
    """The porcelain blocks, with the main checkout's own entry dropped."""
    blocks = [block for block in text.split("\n\n") if block.strip()]
    worktrees = []
    main = os.path.realpath(main_root)
    for block in blocks:
        fields = {}
        for line in block.splitlines():
            key, _, value = line.partition(" ")
            fields[key] = value
        path = fields.get("worktree")
        if not path:
            continue
        if os.path.realpath(path) == main:
            continue
        branch = fields.get("branch")
        if branch and branch.startswith("refs/heads/"):
            branch = branch[len("refs/heads/"):]
        worktrees.append(Worktree(path, fields.get("HEAD"),
                                  branch if branch else None,
                                  "locked" in fields))
    return worktrees


def agent_name(path, agents_root):
    """``<name>`` when *path* is a direct child of ``.git/agents``, else None."""
    root = os.path.realpath(agents_root)
    for candidate in (os.path.realpath(path), os.path.abspath(path)):
        relative = os.path.relpath(candidate, root)
        if relative != os.pardir and not relative.startswith(os.pardir + os.sep):
            parts = relative.split(os.sep)
            if len(parts) == 1 and parts[0] not in ("", os.curdir):
                return parts[0]
    return None


def newest_mtime(directory, now=None):
    """Newest mtime under *directory*, without following symlinks or descending into .git."""
    newest = os.path.getmtime(directory)
    for root, dirs, files in os.walk(directory, followlinks=False):
        dirs[:] = [name for name in dirs
                   if name != ".git" and not os.path.islink(os.path.join(root, name))]
        for name in files:
            try:
                newest = max(newest, os.path.getmtime(os.path.join(root, name)))
            except OSError:
                pass
    return newest


def ref_for(wt):
    """The ref that holds *wt*'s HEAD: its branch, or the detached HEAD itself."""
    return wt.branch or wt.head


def inspect(wt, main_root, main_branch, age_minutes, now=None):
    """Return ``(verdict, reason)`` for one worktree; never mutates anything."""
    if wt.locked:
        return KEEP, "locked by git"
    if os.path.exists(os.path.join(wt.path, LIVE_MARKER)):
        return KEEP, f"live marker ({LIVE_MARKER})"

    present = os.path.isdir(wt.path)
    if present:
        idle = (now if now is not None else time.time()) - newest_mtime(wt.path)
        if idle < age_minutes * 60.0:
            return KEEP, f"live (modified {idle / 60.0:.1f} min ago)"

        dirty = git(["status", "--porcelain", "--", SRC], wt.path).strip()
        if dirty:
            return KEEP, f"uncommitted changes under {SRC}/"

        differs = git_status(["diff", "--quiet", main_branch, "--", SRC], wt.path) != 0
        if differs:
            return KEEP, f"{SRC}/ differs from {main_branch}"
    else:
        ref = ref_for(wt)
        if ref is None:
            return REMOVE, "checkout missing; nothing to compare"
        differs = git_status(["diff", "--quiet", main_branch, ref, "--", SRC],
                             main_root) != 0
        if differs:
            return KEEP, f"{SRC}/ differs from {main_branch}"

    ref = ref_for(wt)
    if ref is not None:
        unmerged = git(["rev-list", f"{main_branch}..{ref}", "--", SRC], main_root).strip()
        if unmerged:
            return KEEP, f"commits not in {main_branch} touch {SRC}/"

    return REMOVE, f"{SRC}/ matches {main_branch} (integrated)"


def archive(wt, main_root, main_branch, rows_root):
    """Write the worktree's diff against *main_branch* to ``.git/agent-rows/<name>.diff``."""
    if os.path.isdir(wt.path):
        diff = git(["diff", main_branch], wt.path)
    else:
        ref = ref_for(wt)
        if ref is None:
            diff = ""
        else:
            diff = git(["diff", main_branch, ref], main_root)
    os.makedirs(rows_root, exist_ok=True)
    target = os.path.join(rows_root, f"{wt.name}.diff")
    with open(target, "w", encoding="utf-8") as handle:
        handle.write(diff)
        if diff and not diff.endswith("\n"):
            handle.write("\n")
    return target


def prune(wt, main_root, main_branch):
    """Remove the worktree and its ``wt-`` branch; the caller has already archived the diff."""
    if os.path.isdir(wt.path):
        git(["worktree", "remove", "--force", wt.path], main_root)
    else:
        git(["worktree", "prune"], main_root)
    if wt.branch and wt.branch.startswith(BRANCH_PREFIX):
        git(["branch", "-D", wt.branch], main_root)
    return wt.branch if wt.branch and wt.branch.startswith(BRANCH_PREFIX) else None


def parse_args(argv=None):
    parser = argparse.ArgumentParser(description=__doc__.splitlines()[0])
    parser.add_argument("--dry-run", action="store_true",
                        help="print the verdicts and change nothing")
    parser.add_argument("--age-minutes", type=float, default=30.0,
                        help="a worktree modified more recently is live (default: 30)")
    parser.add_argument("--main-branch", default="master",
                        help="the branch integrated work has reached (default: master)")
    return parser.parse_args(argv)


def main(argv=None) -> int:
    args = parse_args(argv)
    try:
        cwd = os.getcwd()
        main_root = git(["rev-parse", "--show-toplevel"], cwd).strip()
        agents_root = os.path.join(main_root, AGENTS)
        rows_root = os.path.join(main_root, ROWS)

        if git_status(["rev-parse", "--verify", "--quiet",
                       f"{args.main_branch}^{{commit}}"], main_root) != 0:
            raise Unusable(f"no {args.main_branch} branch in {main_root}")
        dirty = git(["status", "--porcelain", "--", SRC], main_root).strip()
        if dirty:
            raise Unusable(
                f"refusing to prune: the main checkout has changes under {SRC}/; "
                "commit or stash them first")
        if not os.path.isdir(agents_root):
            print(f"worktree-prune: no {AGENTS}/ directory; nothing to do")
            return 0

        all_entries = sorted(name for name in os.listdir(agents_root)
                             if os.path.isdir(os.path.join(agents_root, name)))
        worktrees = parse_worktrees(git(["worktree", "list", "--porcelain"], main_root),
                                    main_root)
        by_name = {}
        for wt in worktrees:
            name = agent_name(wt.path, agents_root)
            if name is not None:
                by_name[name] = wt
    except (Unusable, OSError) as exc:
        print(f"worktree-prune: {exc}", file=sys.stderr)
        return 2

    rows = []
    removes = keeps = failures = 0
    for name in sorted(by_name):
        wt = by_name[name]
        verdict, reason = inspect(wt, main_root, args.main_branch, args.age_minutes)
        rows.append((name, verdict, reason))
        if verdict == KEEP:
            keeps += 1
            continue
        if args.dry_run:
            removes += 1
            continue
        try:
            target = archive(wt, main_root, args.main_branch, rows_root)
            branch = prune(wt, main_root, args.main_branch)
        except (Unusable, OSError) as exc:
            failures += 1
            print(f"{name:<24} {verdict:<7} {reason}; FAILED: {exc}", file=sys.stderr)
            continue
        removes += 1
        removed = "removed worktree" + (f" and branch {branch}" if branch else "")
        print(f"{name:<24} {verdict:<7} {reason}")
        print(f"{'':<24} {'':<7} archived {os.path.relpath(target, main_root)}; {removed}")

    for name, verdict, reason in rows:
        if verdict == KEEP:
            print(f"{name:<24} {verdict:<7} {reason}")
        elif args.dry_run:
            print(f"{name:<24} {verdict:<7} {reason} (dry run)")

    ignored = [name for name in all_entries if name not in by_name]
    for name in ignored:
        print(f"{name:<24} {IGNORE:<7} not a git worktree; left alone")

    total = len(by_name)
    if failures:
        print(f"worktree-prune: {removes} remove, {keeps} keep, {failures} failed", file=sys.stderr)
        return 1
    if not total:
        print("worktree-prune: nothing to do (no agent worktrees)")
    elif not removes:
        print(f"worktree-prune: nothing to do ({keeps} kept)")
    else:
        suffix = " (dry run: nothing changed)" if args.dry_run else ""
        print(f"worktree-prune: {removes} remove, {keeps} keep{suffix}")
    return 0


if __name__ == "__main__":
    sys.exit(main())
