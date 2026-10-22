"""``tools/units/worktree_prune.py`` against synthetic repositories.

Every case builds a throwaway repo in ``tmp_path`` and drives the real CLI, because the
contract is the command: which worktrees disappear, which branches go with them, what the
archive holds, and that a dry run changes nothing.  The synthetic repos have the same shape
as the real one -- worktrees under ``.git/agents/<name>`` on ``wt-<name>`` branches -- but no
build, compiler or retail image is involved.

The age gate is disabled with ``--age-minutes 0`` wherever a worktree must be eligible for
removal: a freshly created worktree is otherwise "live" by definition.  Two tests cover the
gate itself, one through the ``.live`` marker and one through the default window.
"""

from __future__ import annotations

import pathlib
import subprocess
import sys

ROOT = pathlib.Path(__file__).resolve().parents[2]
TOOL = ROOT / "tools" / "units" / "worktree_prune.py"


def git(repo, *args):
    return subprocess.run(["git", *args], cwd=repo, check=True,
                          capture_output=True, text=True).stdout


def make_repo(tmp_path) -> pathlib.Path:
    """A repo with ``src/a.c`` on master and an empty ``.git/agents``."""
    repo = tmp_path / "repo"
    repo.mkdir()
    git(repo, "init", "-q", "-b", "master")
    git(repo, "config", "user.email", "test@example.invalid")
    git(repo, "config", "user.name", "test")
    (repo / "src").mkdir()
    (repo / "src" / "a.c").write_text("int a;\n")
    (repo / "notes.txt").write_text("hi\n")
    git(repo, "add", "-A")
    git(repo, "commit", "-qm", "base")
    (repo / ".git" / "agents").mkdir()
    return repo


def add_worktree(repo, name) -> pathlib.Path:
    path = repo / ".git" / "agents" / name
    git(repo, "worktree", "add", "-q", str(path), "-b", f"wt-{name}")
    return path


def prune(repo, *args):
    return subprocess.run([sys.executable, str(TOOL), *args], cwd=repo,
                          capture_output=True, text=True)


def branches(repo) -> list[str]:
    return git(repo, "branch", "--format=%(refname:short)").split()


def archived(repo, name) -> pathlib.Path:
    return repo / ".git" / "agent-rows" / f"{name}.diff"


def test_a_worktree_whose_source_matches_master_is_removed(tmp_path):
    repo = make_repo(tmp_path)
    worktree = add_worktree(repo, "clean")

    result = prune(repo, "--age-minutes", "0")

    assert result.returncode == 0, result.stderr
    assert "REMOVE" in result.stdout and "1 remove" in result.stdout
    assert not worktree.exists()
    assert "wt-clean" not in branches(repo)
    assert archived(repo, "clean").exists()


def test_a_worktree_with_unmerged_source_is_kept(tmp_path):
    repo = make_repo(tmp_path)
    worktree = add_worktree(repo, "unmerged")
    (worktree / "src" / "b.c").write_text("int b;\n")
    git(worktree, "add", "-A")
    git(worktree, "commit", "-qm", "unmerged unit")

    result = prune(repo, "--age-minutes", "0")

    assert result.returncode == 0, result.stderr
    assert "KEEP" in result.stdout and "differs from master" in result.stdout
    assert worktree.is_dir()
    assert "wt-unmerged" in branches(repo)
    assert not archived(repo, "unmerged").exists()


def test_uncommitted_source_changes_are_never_removed(tmp_path):
    repo = make_repo(tmp_path)
    worktree = add_worktree(repo, "dirty")
    (worktree / "src" / "a.c").write_text("int a; /* edited */\n")

    result = prune(repo, "--age-minutes", "0")

    assert result.returncode == 0, result.stderr
    assert "uncommitted changes under src/" in result.stdout
    assert (worktree / "src" / "a.c").read_text() == "int a; /* edited */\n"
    assert "wt-dirty" in branches(repo)
    assert not archived(repo, "dirty").exists()


def test_a_branch_commit_that_touches_source_is_kept_even_after_a_revert(tmp_path):
    """``src/`` can match master while the branch still holds unmerged source history."""
    repo = make_repo(tmp_path)
    worktree = add_worktree(repo, "reverted")
    (worktree / "src" / "tmp.c").write_text("int t;\n")
    git(worktree, "add", "-A")
    git(worktree, "commit", "-qm", "add")
    git(worktree, "rm", "-q", "src/tmp.c")
    git(worktree, "commit", "-qm", "revert")

    result = prune(repo, "--age-minutes", "0")

    assert result.returncode == 0, result.stderr
    assert "commits not in master touch src/" in result.stdout
    assert worktree.is_dir()
    assert "wt-reverted" in branches(repo)


def test_the_archive_holds_the_worktrees_uncommitted_diff(tmp_path):
    repo = make_repo(tmp_path)
    worktree = add_worktree(repo, "notes")
    (worktree / "notes.txt").write_text("hi\nchanged\n")

    result = prune(repo, "--age-minutes", "0")

    assert result.returncode == 0, result.stderr
    archive = archived(repo, "notes")
    assert archive.is_file()
    assert "+changed" in archive.read_text()
    assert not worktree.exists()


def test_a_dry_run_lists_the_verdict_and_changes_nothing(tmp_path):
    repo = make_repo(tmp_path)
    worktree = add_worktree(repo, "dry")

    result = prune(repo, "--dry-run", "--age-minutes", "0")

    assert result.returncode == 0, result.stderr
    assert "REMOVE" in result.stdout and "dry run" in result.stdout
    assert worktree.is_dir()
    assert "wt-dry" in branches(repo)
    assert not archived(repo, "dry").exists()


def test_a_directory_that_is_not_a_worktree_is_ignored(tmp_path):
    repo = make_repo(tmp_path)
    stranger = repo / ".git" / "agents" / "not-a-worktree"
    stranger.mkdir()
    (stranger / "keep.txt").write_text("mine\n")

    result = prune(repo, "--age-minutes", "0")

    assert result.returncode == 0, result.stderr
    assert "not a git worktree" in result.stdout
    assert (stranger / "keep.txt").read_text() == "mine\n"


def test_a_live_marker_keeps_an_otherwise_integrated_worktree(tmp_path):
    repo = make_repo(tmp_path)
    worktree = add_worktree(repo, "live")
    (worktree / ".live").write_text("")

    result = prune(repo, "--age-minutes", "0")

    assert result.returncode == 0, result.stderr
    assert "live marker" in result.stdout
    assert worktree.is_dir()
    assert "wt-live" in branches(repo)


def test_recent_activity_is_live_under_the_default_window(tmp_path):
    repo = make_repo(tmp_path)
    worktree = add_worktree(repo, "fresh")

    result = prune(repo)                       # default --age-minutes 30

    assert result.returncode == 0, result.stderr
    assert "live (modified" in result.stdout
    assert worktree.is_dir()
    assert "wt-fresh" in branches(repo)


def test_a_dirty_main_checkout_refuses_to_prune(tmp_path):
    repo = make_repo(tmp_path)
    worktree = add_worktree(repo, "clean")
    (repo / "src" / "a.c").write_text("int a; /* half integrated */\n")

    result = prune(repo, "--age-minutes", "0")

    assert result.returncode == 2
    assert "refusing to prune" in result.stderr
    assert worktree.is_dir()
    assert "wt-clean" in branches(repo)
    assert not archived(repo, "clean").exists()


def test_nothing_to_do_exits_zero(tmp_path):
    repo = make_repo(tmp_path)

    result = prune(repo, "--age-minutes", "0")

    assert result.returncode == 0, result.stderr
    assert "nothing to do" in result.stdout
