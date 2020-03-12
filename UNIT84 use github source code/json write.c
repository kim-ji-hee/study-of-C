#include <stdio.h>
#include <stdbool.h>    //bool, true, false�� ���ǵ� ��� ����
#include "parson.h"

int main()
{
    JSON_Value *rootValue;
    JSON_Object *rootObject;

    //�ʱ�ȭ
    rootValue = json_value_init_object();   //JSON_Value ���� �� �ʱ�ȭ
    rootObject = json_value_get_object(rootValue);  //JSON_Value���� JSON_Object�� ����

    //���
    json_object_set_string(rootObject, "Title", "Inception");   //��ü�� Ű�� �߰��ϰ� ���ڿ� ����

    json_object_set_number(rootObject, "Year", 2010);   //��ü�� Ű�� �߰��ϰ� ���� ����
    json_object_set_number(rootObject, "Runtime", 148); 

    json_object_set_string(rootObject, "Genre", "Sci-Fi");  //��ü�� Ű�� �߰��ϰ� ���ڿ� ����
    json_object_set_string(rootObject, "Director", "Christopher Nolan");

    json_object_set_value(rootObject, "Actors", json_value_init_array());   //��ü�� Ű�� �߰��ϰ� �迭 ����

    JSON_Array *actors = json_object_get_array(rootObject, "Actors");   //��ü���� �迭 �����͸� ������

    json_array_append_string(actors, "Leonardo DiCaprio");
    json_array_append_string(actors, "Joseph Gordeon-Levitt");
    json_array_append_string(actors, "Ellen Page");
    json_array_append_string(actors, "Tom Hardy");
    json_array_append_string(actors, "Ken Watanabe");

    json_object_set_number(rootObject, "imdbRating", 8.8);  //��ü�� Ű�� �߰��ϰ� ���� ����

    json_object_set_boolean(rootObject, "KoreaRelease", true);  //��ü�� Ű�� �߰��ϰ� �� �� ����

    json_serialize_to_file_pretty(rootValue, "example.json"); //JSON_Value�� ����� �б� ���� ���ڿ�(pretty)�� ���� �� ���Ͽ� ����

    //����
    json_value_free(rootValue); //JSON_Value�� �Ҵ�� ���� �޸� ����

    return 0;
}