extern int arr[]; extern int *gw; extern void ext(int, int);
void f(void)
{
    int *w = gw;
    int i;
    for (i = 0; i < 10; i++) ext(arr[i], i + 100);
    ext(*w, 0);
}
