#include <stdio.h>

void hello(int count)
{
    if (count == 0)     //종료 조건을 만듬
        return 0;

    printf("Hello, world! %d\n",count);

    hello(--count);
    
}

int main()
{
    hello(5);

    return 0;
}