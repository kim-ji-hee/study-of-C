#include <stdio.h>

extern inline int add(int a, int b)    //인라인 함수로 정의
{
    return a+b;
}

int main()
{
    int num1;

    num1 = add(10, 20);     //인라인 함수 호출

    printf("%d\n", num1);

    return 0;
}