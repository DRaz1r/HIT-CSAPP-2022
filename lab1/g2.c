#include <stdio.h>

#define maxlen 105
int main()
{
    long f[maxlen];
    f[1] = 1; f[2] = 1;
    int i;
    for(i = 3; i <= 101; i ++)
    {
        f[i] = f[i - 1] + f[i - 2];
    }
    printf("f: long\n");
    printf("g: double\n");
    double g = f[100] * 1.0 / f[101];
    printf("fib(100): %ld\n", f[100]);
    printf("fib(101): %ld\n", f[101]);
    printf("g: %lf\n",g);
    return 0;
}