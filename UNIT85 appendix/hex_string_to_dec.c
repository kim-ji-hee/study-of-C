//16������ �� ���ڿ��� 10������ ��ȯ
#define _CRT_SECURE_NO_WARNING
#include <stdio.h>
#include <string.h>
#include <math.h>

int main()
{
    char hexadecimal[20] = "12C";   //16������ �� ���ڿ�
    int decimal = 0;                //10������ ������ ����

    int position = 0;
    for (int i = strlen(hexadecimal) - 1; i >= 0; i--)  //���ڿ��� �������� �ݺ�
    {
        char ch = hexadecimal[i];   //�� �ڸ����� �ش��ϴ� ���ڸ� ����

        if (ch >= 48 && ch <= 57)   //���ڰ� 0~9�̸� (ASCII�ڵ� 48~57)
        {
            decimal += (ch - 48) * pow(16, position);
            //���ڿ��� 0�� �ش��ϴ� ASCII �ڵ� ���� ����
            //16�� �ڸ����� �ŵ������� ���� ����
        }
        else if (ch >= 65 && ch <= 70)  //���ڰ� A~F�̸� (ASCII�ڵ� 65~70) �빮�ڷ� �� 16������ ó��
        {
            decimal += (ch - (65 - 10)) * pow(16, position);
            //���ڿ��� (A�� �ش��ϴ� ASCII �ڵ� �� - 10)�� ����
            //16�� �ڸ����� �ŵ������� ���� ����
        }
        else if (ch >= 97 && ch <= 102) //���ڰ� a~f�̸� (ASCII�ڵ� 97~102) �ҹ��ڷ� �� 16������ ó��
        {
            decimal += (ch - (97 - 10)) * pow(16, position);
            //���ڿ��� (a�� �ش��ϴ� ASCII �ڵ� �� - 10)�� ����
            //16�� �ڸ����� �ŵ������� ���� ����
        }
        position++;
    }
    printf("%d\n",decimal); //300

    return 0;
}
