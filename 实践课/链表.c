#include <stdio.h>
#include <stdlib.h>

#define INITIAL_SIZE 10
#define LISTINCREMENT 5
#define OK 1
#define ERROR 0
#define OVERFLOW -1

typedef struct Node{
    int data;
    struct Node* next;
}Node, *LinkList;

typedef struct headNode{
    int count;
    LinkList first;
}HeadNode;


// 创建节点
LinkList CreateNode(int value){
    LinkList newNode = (LinkList)malloc(sizeof(Node));

    if(newNode == NULL){
        perror("Failed to allocate memory");
        exit(OVERFLOW);
    }

    newNode -> data = value;
    newNode -> next = NULL;
    return newNode;
}


// 创建头节点
HeadNode* CreateHeadNode(){
    HeadNode* head = (HeadNode*)malloc(sizeof(HeadNode));

    if(head == NULL){
        perror("Failed to allocate memory");
        exit(OVERFLOW);
    }

    head -> count = 0;
    head -> first = NULL;
    return head;
}


// 打印链表
void PrintList(HeadNode* head){
    LinkList current = head -> first;
    while(current != NULL){
        printf("%d->", current->data);
        current = current -> next;
    }
    printf("NULL\n");
}


// 尾插法建立链表
void InsertTail(HeadNode* head, int value){
    LinkList newNode = CreateNode(value);
    if(head->first == NULL){
        // 头节点之后空，也就是链表为空的时候，需要接上新节点先
        head -> first = newNode;
    }else{
        LinkList current = head -> first;
        while(current->next != NULL){
            current = current -> next;
        }
        current -> next = newNode;
    }
    head -> count += 1;
}


// 插入
int InsertNode(HeadNode *head, int pos, int value){
    LinkList newNode = CreateNode(value);
    LinkList current = head -> first;

    int temp = 0;

    if (pos == 1) { // 插入到链表头部
        newNode->next = head->first;
        head->first = newNode;
    }else{
        while(current != NULL && temp < pos - 1){
            temp++;
            current = current -> next;
        }

        if(current -> next != NULL) {
            newNode->next = current->next;
            current->next = newNode;
        }else{
            free(newNode);
            return ERROR;
        }
    }
    head->count++;
    return OK;
}


// 按位置删除节点
int DeleteAtPosition(HeadNode *head, int index, int *value) {
    if (index < 1 || index > head->count) return ERROR; // 序号无效

    LinkList current = head -> first;
    LinkList prev = NULL;

    if(index == 1){   // 该情况删除头节点
        *value = current -> data;
        head -> first = current -> next;
        head -> count -= 1;
    }else{
        int pos = 1;
        // 寻找待删除节点的位置
        while (current != NULL && pos < index) {
            prev = current;
            current = current -> next;
            pos++;
        }
        if(current != NULL){
            *value = current->data;
            prev -> next = current -> next;
            free(current);
        }else{
            return ERROR;
        }
    }
    head -> count--;
    return OK;
}


// 按序号查找节点
void GetElemLinklist(HeadNode* head, int index, int *value){
    if (index < 1 || index > head->count) return;  // 序号从1开始

    LinkList current = head -> first;
    int pos = 0;
    while(current != NULL && pos < index){
        current = current -> next;
        pos++;
    }

    if(current != NULL){
        *value = current -> data;
        return;
    }

    return;
}


// 释放链表
void FreeList(HeadNode* head){
    if (!head->first) return;
    LinkList current = head -> first;
    LinkList temp;
    while(current -> next != NULL){
        temp = current;
        current = current -> next;
        free(temp);
    }
    free(current);
    free(head);
}


int main(void){
    HeadNode* head = CreateHeadNode();

    int value_p, n;
    printf("输入需要插入的链表节点个数");
    scanf("%d\n", &n);
    for(int i = 1; i <= n; i++){
        scanf("%d\n", &value_p);
        InsertTail(head, value_p);
    }

    PrintList(head);

    InsertNode(head, 2 ,5);
    PrintList(head);

    int sp, index1;
    printf("需要在第几个位置进行插入");
    scanf("%d\n", &index1);
    GetElemLinklist(head, index1, &sp);
    printf("第%d个节点是%d\n", index1, sp);

    int spp, index2;
    printf("需要删除第几个节点");
    scanf("%d\n", &index2);
    DeleteAtPosition(head, index2, &spp);
    printf("被删除的第%d个节点是%d\n", index2, spp);

    PrintList(head);

    FreeList(head);

    return 0;
}