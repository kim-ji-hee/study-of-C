#include <stdio.h>

#define DEBUG_LEVEL 2

int main()
{
#if DEBUG_LEVEL >= 2
    printf("Debug Level 2\n");
#endif

#if 1
    printf("1\n");
#endif

#if 0
    printf("0\n");
#endif

    return 0;
}