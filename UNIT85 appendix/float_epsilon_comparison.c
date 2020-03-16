//부동소수점 반올림 오차를 고려한 실수 비교 방법
#include <stdio.h>
#include <float.h>  //float의 머신 엡실론 값 FLT_EPSILON이 정의된 헤더 파일
#include <math.h>   //float의 절댓값을 구하는 fabsf 함수를 위한 헤더 파일

int main()
{
    float num1 = 0.0f;
    float num2 = 0.1f;

    for (int i=0; i<10; i++)
    {
        num1 = num1 + num2;
    }

    if (fabsf(num1-1.0f) <= FLT_EPSILON)
    //연산한 값과 비교할 값의 차이를 구하고 절댓값으로 만든 뒤
    //FLT_EPSILON 보다 작거나 같은지 판단
    //오차가 머신 엡실론 이하라면 같은 값으로 봄
        printf("true\n");
    else
        printf("false\n");
    
    return 0;
}
