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

char *getString(JSON *json, char *key)  //Ű�� �ش��ϴ� ���ڿ��� �������� �Լ�
{
    for (int i=0; i<TOKEN_COUNT; i++)   //��ū ������ŭ �ݺ�
    {
        if(json->tokens[i].type == TOKEN_STRING && strcmp(json->tokens[i].string, key)==0)
        //��ū ������ ���ڿ��̸鼭 ��ū�� ���ڿ��� Ű�� ��ġ�ϸ�
        {
            if(json->tokens[i+1].type == TOKEN_STRING)  //�ٷ� ���� ��ū(i+1)�� ���ڿ��̸�
                return json->tokens[i+1].string;    //�ٷ� �ڿ� �ִ� ��ū�� ���ڿ� ��ȯ
        }

    }
    return NULL;    //Ű�� ã�� �������� NULL �� ��ȯ
}


char *getArrayString(JSON *json, char *key, int index)  //Ű�� �ش��ϴ� �迭 �� �ε����� �����Ͽ� ���ڿ��� �������� �Լ�
{
    for (int i=0; i<TOKEN_COUNT; i++)   //��ū ������ŭ �ݺ�
    {
        if(json->tokens[i].type == TOKEN_STRING && strcmp(json->tokens[i].string, key)==0)
        //��ū ������ ���ڿ��̸鼭 ��ū�� ���ڿ��� Ű�� ��ġ�ϸ�
        {
            if(json->tokens[i+1+index].type == TOKEN_STRING &&
               json->tokens[i+1+index].isArray == true)  
               //�ٷ� ���� ��ū (i+1)���� �迭�� ���
               //�ε����� ������ ��ū�� ���ڿ��̸鼭 �迭�̸�
                return json->tokens[i+1+index].string;    //�ش� ��ū�� ���ڿ� ��ȯ
        }
    }
    return NULL;    //Ű�� ã�� �������� NULL �� ��ȯ
}

int getArrayCount(JSON *json, char *key)    //Ű�� �ش��ϴ� �迭�� ��� ������ ���ϴ� �Լ�
{
    for (int i=0; i<TOKEN_COUNT; i++)   //��ū�� ������ŭ �ݺ�
    {
        if(json->tokens[i].type == TOKEN_STRING && strcmp(json->tokens[i].string, key)==0)
        //��ū�� ������ ���ڿ��̸鼭 ��ū�� ���ڿ��� Ű�� ��ġ�Ѵٸ�
        {
            int j=0;
            while(json->tokens[i+1+j].isArray==true)    //�ٷ� ���� ��ū(i+1)���� isArray�� true�� ��ū�� ������ ��� ��ȯ
                j++;

            return j;
        }
    }
    return 0;   //Ű�� ã�� �������� 0�� ��ȯ
}

int getNumber(JSON *json, char *key)    //Ű�� �ش��ϴ� ���ڸ� �������� �Լ�
{
    for (int i=0; i<TOKEN_COUNT; i++)   //��ū�� ������ŭ �ݺ�
    {
        if(json->tokens[i].type == TOKEN_STRING && strcmp(json->tokens[i].string, key)==0)
        //��ū�� ������ �����̸鼭 ��ū�� ���ڿ��� Ű�� ��ġ�Ѵٸ�
        {
            if(json->tokens[i+1].type==TOKEN_NUMBER)   //�ٷ� ���� ��ū(i+1)�� �����̸�
                return json->tokens[i+1].number;    //�ٷ� �ڿ� �ִ� ��ū�� ���� ��ȯ
        }
    }
    return 0.0;   //Ű�� ã�� �������� 0�� ��ȯ
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

    printf("Title: %s\n", getString(&json, "Title"));
    printf("Year: %d\n", (int)getNumber(&json, "Year"));
    printf("Runtime: %d\n", (int)getNumber(&json, "Runtime"));
    printf("Genre: %s\n", getString(&json, "Genre"));
    printf("Director: %s\n", getString(&json, "Director"));

    printf("Actors:\n");
    int actors = getArrayCount(&json, "Actors");    //Actors �迭�� ������ ����
    for(int i=0; i<actors; i++) //�迭�� ��� ������ŭ �ݺ�
        printf("    %s\n", getArrayString(&json, "Actors", i)); //�ε����� �����Ͽ� ���ڿ��� ������

    printf("imdbRating: %f\n", getNumber(&json, "imdbRating")); //imdbRating�� �� ���

    freeJSON(&json);    //json�� �Ҵ�� ���� �޸� ����
    free(doc);  //���� ���� �޸� ����

    return 0;
}