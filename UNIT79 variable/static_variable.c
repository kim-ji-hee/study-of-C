#include <stdio.h>

void increaseNumber()
{
    static int num1 = 0;    //정적변수 이면서 지역변수

    printf("%d\n", num1);

    num1++;
}

int main()
{
    increaseNumber();
    increaseNumber();
    increaseNumber();
    increaseNumber();

    return 0;
}