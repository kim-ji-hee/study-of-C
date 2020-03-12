#include <stdio.h>
#include <stdbool.h>    //bool, true, false가 정의된 헤더 파일
#include "parson.h"

int main()
{
    JSON_Value *rootValue;
    JSON_Object *rootObject;

    //초기화
    rootValue = json_value_init_object();   //JSON_Value 생성 및 초기화
    rootObject = json_value_get_object(rootValue);  //JSON_Value에서 JSON_Object를 얻음

    //사용
    json_object_set_string(rootObject, "Title", "Inception");   //개체에 키를 추가하고 문자열 저장

    json_object_set_number(rootObject, "Year", 2010);   //객체에 키를 추가하고 숫자 저장
    json_object_set_number(rootObject, "Runtime", 148); 

    json_object_set_string(rootObject, "Genre", "Sci-Fi");  //객체에 키를 추가하고 문자열 저장
    json_object_set_string(rootObject, "Director", "Christopher Nolan");

    json_object_set_value(rootObject, "Actors", json_value_init_array());   //객체에 키를 추가하고 배열 생성

    JSON_Array *actors = json_object_get_array(rootObject, "Actors");   //객체에서 배열 포인터를 가져옴

    json_array_append_string(actors, "Leonardo DiCaprio");
    json_array_append_string(actors, "Joseph Gordeon-Levitt");
    json_array_append_string(actors, "Ellen Page");
    json_array_append_string(actors, "Tom Hardy");
    json_array_append_string(actors, "Ken Watanabe");

    json_object_set_number(rootObject, "imdbRating", 8.8);  //객체에 키를 추가하고 숫자 저장

    json_object_set_boolean(rootObject, "KoreaRelease", true);  //객체에 키를 추가하고 불 값 저장

    json_serialize_to_file_pretty(rootValue, "example.json"); //JSON_Value를 사람이 읽기 쉬운 문자열(pretty)로 만든 뒤 파일에 저장

    //해제
    json_value_free(rootValue); //JSON_Value에 할당된 동적 메모리 해제

    return 0;
}