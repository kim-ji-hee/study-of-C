#include <stdio.h>
#include <stdlib.h>

struct NODE {
    struct NODE *next;
    int data;
};

void addFirst(struct NODE *target, int data)
{
    struct NODE *newNode = malloc(sizeof(struct NODE));
    newNode->next = target->next;
    newNode->data = data;

    target->next = newNode;
}

int main()
{
    struct NODE *head = malloc(sizeof(struct NODE));

    head -> next = NULL;

    addFirst(head, 10);
    addFirst(head, 20);
    addFirst(head, 30);

    struct NODE *curr = head -> next;

    while(curr!=NULL)
    {
        printf("%d\n", curr->data);
        curr = curr->next;
    }

    curr = head -> next;    //연결 리스트 순회용 포인터에 첫 번째 노드의 주소 저장

    while(curr!=NULL)   //포인터가 NULL이 아닐 때 계속 반복
    {
        struct NODE *next = curr->next;     //현재 노드의 다음 노드 주소를 임시로 저장
        free(curr);      //현재 노드 메모리 해제
        curr = next;    //포인터에 다음 노드의 주소 저장
    }

    free(head);

    return 0;
}