#include <stdio.h>
#include "parson.h"

int main()
{
    JSON_Value *rootValue;
    JSON_Object *rootObject;    //{

    //�ʱ�ȭ
    rootValue = json_parse_file("example.json");    //JSON ������ �о �Ľ�
    rootObject = json_value_get_object(rootValue);  //JSON_Value���� JSON_Object�� ����

    //���
    printf("Title: %s\n", json_object_get_string(rootObject, "Title")); //��ü���� Ű�� �ش��ϴ� ���ڿ��� ������

    printf("Year: %d\n", (int)json_object_get_number(rootObject, "Year"));  //��ü���� Ű�� �ش��ϴ� ���ڸ� ������
    printf("Runtime: %d\n", (int)json_object_get_number(rootObject, "Runtime"));

    printf("Genre: %s\n", json_object_get_string(rootObject, "Genre")); //��ü���� Ű�� �ش��ϴ� ���ڿ��� ������
    printf("Director: %s\n", json_object_get_string(rootObject, "Director"));

    printf("Actors:\n");
    JSON_Array *array = json_object_get_array(rootObject, "Actors"); //��ü���� Ű�� �ش��ϴ� �迭�� ������
    for(int i=0; i<json_array_get_count(array); i++)    //�迭�� ��� ������ŭ �ݺ�
    {
        printf("  %s\n", json_array_get_string(array, i));  //�迭�� �ε����� �����Ͽ� ���ڿ��� ������
    }

    printf("imdbRating: %f\n", json_object_get_number(rootObject, "imdbRating"));  //��ü���� Ű�� �ش��ϴ� ���ڸ� ������

    printf("KoreaRelease: %d\n", json_object_get_boolean(rootObject, "KoreaRelease"));  //��ü���� Ű�� �ش��ϴ� �� ���� ������

    //����
    json_value_free(rootValue); //JSON_Value�� �Ҵ�� ���� �޸� ����

    return 0;
}