#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void getFileRead(FILE *fp, int offset, int size)
{
    char *buffer;
    buffer = malloc(size+1);
    memset(buffer, 0, size+1);

    if(offset>=0)
    fseek(fp, offset, SEEK_SET);
    else 
    fseek(fp, offset, SEEK_END);

    fread(buffer, size, 1, fp);
    printf("%s\n",buffer);

    free(buffer);
}


int main()
{
    FILE *fpw = fopen("word.txt", "w");
    fputs("Hello, world!",fpw);
    FILE *fpr = fopen("word.txt", "r");

    getFileRead(fpr,7,4);
    getFileRead(fpr,-6,2);

    fclose(fpw);
    fclose(fpr);

    return 0;    
}
