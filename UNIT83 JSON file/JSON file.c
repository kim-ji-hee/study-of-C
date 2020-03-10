#define _CRT_SECURE_NO_WARNINGS //fopen ���� ���� ���� ������ ���� ����
#include <stdio.h>      //���� ó�� �Լ��� ����� ��� ����
#include <stdlib.h>     //malloc, free �Լ��� ����� ��� ����
#include <stdbool.h>    //bool, true, false�� ���ǵ� ��� ����
#include <string.h>     //strchr, memset, memcpy �Լ��� ����� ��� ����

typedef enum _TOKEN_TYPE {   //��ū ���� ������
    TOKEN_STRING,
    TOKEN_NUMBER,
} TOKEN_TYPE;

typedef struct _TOKEN {
    TOKEN_TYPE type; //��ū ����
    union {    //�� ���� �� �� ������ ������ ���̹Ƿ� ����ü�� ����
        char *string;
        double number;
    };
    bool isArray;   //���� ��ū�� �迭���� ǥ��
} TOKEN;

#define TOKEN_COUNT 20  //��ū�� �ִ� ����

typedef struct _JSON {
    TOKEN tokens[TOKEN_COUNT];  //��ū �迭
} JSON;

char *readFile(char *filename, int *readSize)   //������ �о ���ڿ� �����͸� ��ȯ�ϴ� �Լ�
{
    FILE *fp = fopen(filename, "rb");
    if(fp == NULL)
        return NULL;

    int size;
    char *buffer;

    //���� ũ�� ���ϱ�
    fseek(fp, 0, SEEK_END);
    size = ftell(fp);
    fseek(fp, 0, SEEK_SET);
    
    //���� ũ�� + NULL ������ŭ �޸𸮸� �Ҵ��ϰ� 0���� �ʱ�ȭ
    buffer = malloc(size + 1);
    memset(buffer, 0, size + 1);

    //���� ���� �б�
    if(fread(buffer, size, 1, fp)<1)
    {
        *readSize = 0;
        free(buffer);
        fclose(fp);
        return NULL;
    }

    //���� ũ�⸦ �Ѱ���
    *readSize = size;
    fclose(fp); //���� ������ �ݱ�
    return buffer;
}

void parseJSON(char *doc, int size, JSON *json) //JSON �Ľ� �Լ�
{
    int tokenIndex = 0;
    int pos = 0;    //���� �˻� ��ġ�� �����ϴ� ����

    if(doc[pos] != '{') //������ ������ {���� �˻�
        return;

    pos++;  //���� ���ڷ�

    while(pos < size)   //���� ũ�⸸ŭ �ݺ�
    {
        switch(doc[pos])    //������ ������ ���� �б�
        {
            case '"' :      //���ڰ� "�̸� ���ڿ�
            {
                char *begin = doc + pos + 1; //���ڿ��� ���� ��ġ�� ����. �� ���� "�� �����ϱ� ���� +1

                char *end = strchr(begin, '"'); //���ڿ��� �� ��ġ�� ����. ���� "�� ��ġ
                if(end==NULL)   //"�� ������ �߸��� �����̹Ƿ�
                    break;      //�ݺ��� ����

                int stringLength = end - begin;  //���ڿ��� ���� ���̴� �� ��ġ - ������ġ

                json->tokens[tokenIndex].type = TOKEN_STRING;   //��ū�迭�� ���ڿ� ����(��ū���� ���ڿ�)
                json->tokens[tokenIndex].string = malloc(stringLength+1);   //���ڿ� ���� + NULL ������ŭ �޸� �Ҵ�
                memset(json->tokens[tokenIndex].string,0,stringLength+1);   //�Ҵ��� �޸𸮸� 0���� �ʱ�ȭ

                memcpy(json->tokens[tokenIndex].string, begin, stringLength);
                //�������� ���ڿ��� ��ū�� ����
                //���ڿ� ���� ��ġ���� ���ڿ� ���̸�ŭ ����

                tokenIndex++; //��ū �ε��� ����

                pos = pos + stringLength + 1; //���� ��ġ + ���ڿ� ���� + "(+1)
            }
            break;

            case '[' :      //���ڰ� [�̸� �迭
            {
                pos++;  //���� ���ڷ�

                while(doc[pos] != ']')  //�ݴ� ]�� ������ �ݺ� ����
                {
                    if(doc[pos]=='"')   //���ڰ� "�̸� ���ڿ�
                    {
                        char *begin = doc + pos + 1; //���ڿ��� ���� ��ġ�� ����. �� ���� "�� �����ϱ� ���� + 1

                        char *end = strchr(begin, '"'); //���ڿ��� �� ��ġ�� ����. ���� "�� ��ġ
                        if(end == NULL) //"�� ������ �߸��� �����̹Ƿ�
                            break;      //�ݺ��� ����

                        int stringLength = end - begin; //���ڿ��� ���� ���̴� �� ��ġ - ���� ��ġ

                        json->tokens[tokenIndex].type = TOKEN_STRING;   //��ū �迭�� ���ڿ� ����
                        json->tokens[tokenIndex].string = malloc(stringLength+1); //���ڿ� ���� + NULL ������ŭ �޸� �Ҵ�
                        json->tokens[tokenIndex].isArray = true;    //���� ���ڿ��� �迭�� ���
                        memset(json->tokens[tokenIndex].string, 0, stringLength+1); //�Ҵ��� �޸𸮸� 0���� �ʱ�ȭ

                        memcpy(json->tokens[tokenIndex].string, begin, stringLength);
                        //�������� ���ڿ��� ��ū�� ����
                        //���ڿ� ���� ��ġ���� ���ڿ� ���̸�ŭ�� ����

                        tokenIndex++; //��ū �ε��� ����

                        pos = pos + stringLength + 1; //���� ��ġ + ���ڿ� ���� + "(+1)
                    }
                    pos++;  //���� ���ڷ�
                }
            }
            break;

            case '0': case '1': case '2': case '3': case '4': case '5': case '6':
            case '7': case '8': case '9': case '-': //���ڰ� �����̸�, -�� ������ ��
            {
                char *begin = doc + pos;    //���ڿ��� ���� ��ġ�� ����
                char *end;
                char *buffer;

                end = strchr(doc + pos, ',');   //���ڿ��� �� ��ġ�� ����. ,�� �����ų�
                if (end == NULL)
                {
                    end = strchr(doc+pos, '}'); // }�� ������ ���ڿ��� ����
                    if(end == NULL) // }�� ������ �߸��� �����̹Ƿ�
                        break;      // �ݺ��� ����
                }

                int stringLength = end - begin; //���ڿ��� ���� ���̴� �� ��ġ - ���� ��ġ

                buffer = malloc(stringLength + 1);  //���ڿ��� ���� + NULL ������ŭ �޸� �Ҵ�
                memset(buffer, 0, stringLength+1);  //�Ҵ��� �޸𸮸� 0���� �ʱ�ȭ

                memcpy(buffer, begin, stringLength);    
                //�������� ���ڿ��� ���ۿ� ����
                //���ڿ� ���� ��ġ���� ���ڿ� ���̸�ŭ�� ����

                json->tokens[tokenIndex].type = TOKEN_NUMBER;   //��ū ������ ����
                json->tokens[tokenIndex].number = atof(buffer); //���ڿ��� ���ڷ� ��ȯ�Ͽ� ��ū�� ����

                free(buffer);   //���� ����

                tokenIndex++;   //��ū �ε��� ����

                pos = pos + stringLength + 1;   //���� ��ġ + ���ڿ� ���� + , �Ǵ� } (+1)
            }
            break;
        }

        pos++;  //���� ���ڷ�
    }

}

void freeJSON(JSON *json)   //JSON ���� �Լ�
{
    for(int i=0; i<TOKEN_COUNT; i++)
    {
        if(json->tokens[i].type == TOKEN_STRING)    //��ū ������ ���ڿ��̸�
            free(json->tokens[i].string);           //���� �޸� ����
    }
}

int main()
{
    int size;   //���� ũ��

    char *doc = readFile("example.json", &size); //���Ͽ��� JSON ������ ����, ���� ũ�⸦ ����
    if (doc == NULL)
        return -1;

    JSON json = {0, };  //JSON ����ü ���� ���� �� �ʱ�ȭ

    parseJSON(doc, size, &json);    //JSON ���� �Ľ�

    printf("Title: %s\n", json.tokens[1].string);
    printf("Genre: %s\n", json.tokens[3].string);
    printf("Director: %s\n", json.tokens[5].string);

    printf("Actors:\n");
    printf("    %s\n", json.tokens[7].string);
    printf("    %s\n", json.tokens[8].string);
    printf("    %s\n", json.tokens[9].string);
    printf("    %s\n", json.tokens[10].string);
    printf("    %s\n", json.tokens[11].string);

    freeJSON(&json);    //json�� �Ҵ�� ���� �޸� ����
    free(doc);  //���� ���� �޸� ����

    return 0;
}