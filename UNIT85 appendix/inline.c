#include <stdio.h>

extern inline int add(int a, int b)    //�ζ��� �Լ��� ����
{
    return a+b;
}

int main()
{
    int num1;

    num1 = add(10, 20);     //�ζ��� �Լ� ȣ��

    printf("%d\n", num1);

    return 0;
}