#include <stdio.h>

void hello()
{
    printf("Hello, world!\n");

    hello();    // 함수 호출은 메모리의 스택을 사용
                //스택이 넘쳐서 스택 오버플로우(stack overflow) 에러 발생
}

int main()
{
    hello();

    return 0;
}