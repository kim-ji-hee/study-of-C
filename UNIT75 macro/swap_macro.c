#include <stdio.h>

#define SWAP(a, b, type) do{ \
    type temp;  \
    temp = a;   \
    a = b;      \
    b = temp;   \
} while(0)

int main()
{
    int num1 = 10;
    int num2 = 20;

    SWAP(num1, num2, int);
    printf("%d %d\n", num1, num2);

    float num3 = 1.5f;
    float num4 = 3.8f;

    SWAP(num3, num4, float);
    printf("%f %f\n", num3, num4);

    return 0;
}