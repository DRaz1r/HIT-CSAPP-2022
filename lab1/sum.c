#include <stdio.h>

int sum(int a[], unsigned len)
{
    int i, sum = 0;
    for(i = 0; i <= len - 1; i ++ )
    {
        sum += a[i];
    }
    return sum;
}

int main()
{
    int a[] = {4, 5, 6, 7, 8};
    int len = 5;
    int b = sum(a, 0);
    printf("b: %d\n", b);
    return 0;
}