#include <stdio.h>

#define USB

int main()
{
#ifdef PS2
    printf("PS2\n");
#elif defined USB
    printf("USB\n");
#else
    printf("지원하지 않는 장치입니다.\n");
#endif

    return 0;
}