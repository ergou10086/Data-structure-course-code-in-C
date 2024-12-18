#include <stdio.h>
#include <stdlib.h>

#define INITIAL_SIZE 10
#define LISTINCREMENT 5
#define OK 1
#define ERROR 0
#define OVERFLOW -1

typedef struct Node {
    int data;       // 数据元素
    struct Node *next;  // 指向下一个节点的指针
} Node, *LinkList;
// Node 实际上就是 struct Node 的别名
// LinkList是指向 Node 结构体的指针，LinkList 就是 Node* 的别名，LinkList 可以被用来表示链表中的节点


// 头节点结构
typedef struct {
    int count;      // 链表中节点的个数
    LinkList first; // 指向链表第一个节点的指针
} HeadNode;


// 创建一个新的节点
LinkList CreateNode(int value){
    // 为新节点分配内存
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
    if (head == NULL) {
        perror("Failed to allocate memory");
        exit(OVERFLOW);
    }
    head->count = 0;
    head->first = NULL;
    return head;
}


// 打印链表
void PrintList(HeadNode* head){
    LinkList current = head->first;
    while(current != NULL){
        printf("%d -> ", current->data);
        current = current->next;
    }
    printf("NULL\n");
}


// 尾插法建立链表
void InsertNode(HeadNode *head, int value){
    LinkList newNode = CreateNode(value);
    if (head->first == NULL) {
        head->first = newNode;
    }else{
        LinkList current = head -> first;
        while(current -> next != NULL){
            current = current -> next;
        }
        current -> next = newNode;
    }
    head -> count++;
}


// 头插法建立链表
// 逆位序输入 n 个元素的值，建立带表头结点的单链表 L
void InsertAtHead(HeadNode *head, int value) {
    LinkList newNode = CreateNode(value);
    // 和别的一样的连接方式
    newNode->next = head->first;
    head->first = newNode;
    head->count++;
}


// 插入操作
int InsertAtPosition(HeadNode *head, int index, int value) {
    if (index < 1 || index > head->count + 1) return ERROR; // 位置无效

    LinkList newNode = CreateNode(value);

    if (index == 1) { // 插入到链表头部
        newNode->next = head->first;
        head->first = newNode;
    }else{
        LinkList current = head -> first;
        int pos = 1;

        // 寻找插入位置的前一个节点
        while (current != NULL && pos < index - 1) {
            current = current->next;
            pos++;
        }

        if(current != NULL){
            // 新节点的指针指向原链表中插入位置前一个节点的后一个节点
            // 然后再让原链表中插入位置前一个节点的指针指向新节点
            // 避免节点丢失
            newNode->next = current->next;
            current -> next = newNode;
        }else{
            free(newNode);
            return ERROR;
        }
    }
    head->count++;
    return OK;
}


// 按序号查找
int GetElem_Linklist(HeadNode* head, int index, int *value){
    if (index < 1 || index > head->count) return ERROR;  // 序号从1开始

    LinkList current = head -> first;
    int pos = 1;

    // 不断移动指针，移动到index的位置，但是需要这个位置非空才能进行
    while(current != NULL && pos < index){
        current = current -> next;
        pos++;
    }

    if(current != NULL){
        *value = current -> data;
        return OK;
    }

    return ERROR;
}


// 按值查找
int FindElem_Linklist(HeadNode* head, int value, int *index) {
    LinkList current = head -> first;
    int pos = 1;

    while(current != NULL){
        if(current->data == value){
            *index = pos;
            return OK;
        }
        current = current -> next;
        pos++;
    }
    return ERROR;
}


// 按序号删除
int DeleteAtPosition(HeadNode *head, int index, int *value) {
    if (index < 1 || index > head->count) return ERROR; // 序号无效

    LinkList current = head -> first;
    LinkList prev = NULL;

    // 删除头节点的情况
    if(index == 1){
        *value = current -> data;   // 存储被删除节点的值
        head -> first = current -> next;  // 修改头节点指针
        free(current);  // 释放被删除节点的内存
    }else{
        int pos = 1;
        // 寻找待删除节点的位置
        while (current != NULL && pos < index) {
            prev = current;    // prev记录删除节点的前一个节点
            current = current -> next;
            pos++;
        }

        if(current != NULL){
            *value = current->data;  // 存储被删除节点的值
            prev->next = current->next;  // 修改前一个节点的指针，指向被删除节点的next，把要删除的节点略过
            free(current);  // 释放被删除节点的内存
        }else{
            return ERROR;
        }
    }
    head->count--;
    return OK;
}


int DestoryLinkList(HeadNode *head){
    LinkList current = head->first;
    LinkList next;
    while (current!= NULL) {
        next = current->next;
        free(current);
        current = next;
    }
    free(head);  // 释放头节点
    return 0;
}



int main(void){
    HeadNode* head = CreateHeadNode();

    InsertNode(head, 10);
    InsertNode(head, 20);
    InsertNode(head, 30);
    PrintList(head);

    // 按序号查找测试
    int value, index = 2;
    if (GetElem_Linklist(head, index, &value) == OK) {
        printf("Element at index %d: %d\n", index, value);
    } else {
        printf("Failed to get element at index %d\n", index);
    }

    // 按值查找测试
    int searchValue = 30;
    if (FindElem_Linklist(head, searchValue, &index) == OK) {
        printf("Element %d found at index %d\n", searchValue, index);
    } else {
        printf("Element %d not found\n", searchValue);
    }


    // 插入新节点测试
    int newValue = 15, index1 = 2;
    if (InsertAtPosition(head, index1, newValue) == OK) {
        printf("Inserted %d at position %d\n", newValue, index1);
    } else {
        printf("Failed to insert %d at position %d\n", newValue, index1);
    }
    PrintList(head);


    // 按序号删除测试
    int deletedValue, deleteIndex = 1;
    if (DeleteAtPosition(head, deleteIndex, &deletedValue) == OK) {
        printf("Deleted element at index %d: %d\n", deleteIndex, deletedValue);
    } else {
        printf("Failed to delete element at index %d\n", deleteIndex);
    }
    PrintList(head);

    // 头插法测试
    int n, vap;
    scanf("%d ", &n);
    for(int i = n; i > 0; i--){
        scanf("%d", &vap);
        InsertAtHead(head, vap);
    }
    PrintList(head);

    return 0;
}
