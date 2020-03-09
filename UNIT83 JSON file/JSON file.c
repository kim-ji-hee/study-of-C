
typedef enum_TOKEN_TYPE {   //��ū ���� ������
    TOKEN_STRING,
    TOKEN_NUMBER,
} TOKEN_TYPE;

typedef struct _TOKEN {
    TOKEN_TYPE type; //��ū ����
    uniont {    //�� ���� �� �� ������ ������ ���̹Ƿ� ����ü�� ����
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
        }

        pos++;  //���� ���ڷ�
    }

}

void freeJSON(JSON *json)   //JSON ���� �Լ�
{
    for(int i=0; i<TOKEN_COUNT; i++)
    {
        if (int i=0; i<TOKEN_COUNT; i++)
        {
            if(json->tokens[i].type == TOKEN_STRING)    //��ū ������ ���ڿ��̸�
                free(json->tokens[i].string);           //���� �޸� ����
        }
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

    freeJSON(&json);    //json�� �Ҵ�� ���� �޸� ����
    free(doc);  //���� ���� �޸� ����

    return 0;
}