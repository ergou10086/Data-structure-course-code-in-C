#include <stdio.h>
#include <stdlib.h>

typedef struct Node {
    int data;
    struct Node* next;
} Node;

typedef struct CircularList {
    Node* head;
} CircularList;

// 初始化循环链表
CircularList* initList() {
    CircularList* list = (CircularList*)malloc(sizeof(CircularList));
    list->head = NULL;
    return list;
}

// 头插法
void insertHead(CircularList* list, int data) {
    Node* newNode = (Node*)malloc(sizeof(Node));
    newNode->data = data;
    if (!list->head) {
        newNode->next = newNode;  // 指向自身
        list->head = newNode;
    } else {
        Node* tail = list->head;
        while (tail->next != list->head) {
            tail = tail->next;
        }
        newNode->next = list->head;
        tail->next = newNode;
        list->head = newNode;
    }
}

// 尾插法
void insertTail(CircularList* list, int data) {
    Node* newNode = (Node*)malloc(sizeof(Node));
    newNode->data = data;
    if (!list->head) {
        newNode->next = newNode;
        list->head = newNode;
    } else {
        Node* tail = list->head;
        while (tail->next != list->head) {
            tail = tail->next;
        }
        tail->next = newNode;
        newNode->next = list->head;
    }
}

// 删除节点
void deleteNode(CircularList* list, int data) {
    if (!list->head) return;
    Node *current = list->head, *prev = NULL;
    do {
        if (current->data == data) {
            if (prev) {
                prev->next = current->next;
            } else {
                // 头节点的情况
                Node* tail = list->head;
                while (tail->next != list->head) {
                    tail = tail->next;
                }
                tail->next = current->next;
                list->head = current->next == list->head ? NULL : current->next;
            }
            free(current);
            return;
        }
        prev = current;
        current = current->next;
    } while (current != list->head);
}

// 按值查找
Node* findByValue(CircularList* list, int value) {
    if (!list->head) return NULL;
    Node* current = list->head;
    do {
        if (current->data == value) {
            return current;
        }
        current = current->next;
    } while (current != list->head);
    return NULL;
}

// 按节点查找
Node* findByNode(CircularList* list, int index) {
    if (!list->head || index < 0) return NULL;
    Node* current = list->head;
    int count = 0;
    do {
        if (count == index) {
            return current;
        }
        current = current->next;
        count++;
    } while (current != list->head);
    return NULL;
}

// 排序（简单冒泡排序）
void sortList(CircularList* list) {
    if (!list->head) return;
    int swapped;
    do {
        Node* current = list->head;
        Node* prev = NULL;
        swapped = 0;
        do {
            if (current->data > current->next->data) {
                // 交换数据
                int temp = current->data;
                current->data = current->next->data;
                current->next->data = temp;
                swapped = 1;
            }
            prev = current;
            current = current->next;
        } while (current->next != list->head);
    } while (swapped);
}

// 打印链表
void printList(CircularList* list) {
    if (!list->head) return;
    Node* current = list->head;
    do {
        printf("%d ", current->data);
        current = current->next;
    } while (current != list->head);
    printf("\n");
}

// 释放链表
void freeList(CircularList* list) {
    if (!list->head) return;
    Node* current = list->head;
    Node* temp;
    do {
        temp = current;
        current = current->next;
        free(temp);
    } while (current != list->head);
    free(list);
}

int main() {
    CircularList* list = initList();
    insertHead(list, 10);
    insertTail(list, 20);
    insertTail(list, 30);
    printList(list);

    deleteNode(list, 20);
    printList(list);

    Node* found = findByValue(list, 10);
    if (found) printf("Found: %d\n", found->data);

    sortList(list);
    printList(list);

    freeList(list);
    return 0;
}
