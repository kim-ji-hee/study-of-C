#include <stdio.h>

extern int num1;    //다른소스파일에 있는 정적 전역 변수는 extern으로 사용할 수 없음

int main()
{
    printf("%d\n", num1);

    return 0;
}