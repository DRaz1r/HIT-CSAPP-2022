#include <stdio.h>
#include <string.h>

#define maxlen 105
long f[maxlen];

long fib(int x)
{
    if(f[x] == -1)
    {
        return f[x] = fib(x - 2) + fib(x - 1);
    }else
    {
        return f[x];
    }
}

int main()
{
    memset(f, -1, sizeof (f));
    f[1] = 1; f[2] = 1;
    long f_100 = fib(100);
    long f_101 = fib(101);
    printf("f: long\n");
    printf("g: double\n");
    double g = f_100 * 1.0 / f_101;
    printf("fib(100): %ld\n", f_100);
    printf("fib(101): %ld\n", f_101);
    printf("g: %lf\n",g);
    return 0;
}