#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>

int sum(int n)
{
    if (n == 1)
        return 1;

    return n+sum(n-1);
}

int main()
{
    int n = 0;

    scanf("%d", &n);

    printf("%d\n", sum(n));

    return 0;
}