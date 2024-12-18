#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

// 定义链表节点
typedef struct Node {
    int data;               // 节点数据
    struct Node* next;      // 指向下一个节点的指针
} QNode, *QueuePtr;

// 定义队列结构体
typedef struct Queue {
    QueuePtr front;           // 指向队列头部的指针
    QueuePtr rear;            // 指向队列尾部的指针
} Lqueue;


// 初始化队列
Lqueue *InitQueue(){
    Lqueue *queue = (Lqueue *) malloc(sizeof(Lqueue));
    if(!queue){
        printf("内存分配失败\n");
        return NULL;
    }
    queue->front = NULL;
    queue->rear = NULL;
    return queue;
}


// 入队
void Enqueue(Lqueue * queue, int value) {
    QNode *newNode = (QNode *) malloc(sizeof(QNode));
    if(!newNode){
        printf("内存分配失败\n");
        return;
    }
    newNode -> data = value;
    newNode -> next = NULL;

    if(queue -> rear){
        queue -> rear -> next = newNode;   // 将当前尾节点的next指向新节点
    }
    queue -> rear = newNode;  // 更新队列尾部，始终在最前面

    if (!queue->front) {
        queue->front = newNode;      // 如果队列是空的，更新头部
    }
}


// 出队
int dequeue(Lqueue* queue) {
    if(!queue -> front){
        printf("队列为空，无法出队\n");
        return -1;
    }
    QNode *temp = queue -> front;
    int value = temp -> data;

    queue -> front = queue -> front -> next;  // 先空过要删除的节点

    if (queue -> rear == temp) {
        queue -> rear = queue -> front;  // 如果队列为空，尾部也设置为NULL
    }
    free(temp);
    return value;
}


// 获取头节点元素
int front(Lqueue* queue) {
    if (!queue->front) {
        printf("队列为空\n");
        return -1; // 可以返回一个标志表示队列为空
    }
    return queue->front->data;
}


// 判空
bool isEmpty(Lqueue* queue) {
    return queue->front == NULL;
}


// 销毁队列
void destroyQueue(Lqueue* queue) {
    while (!isEmpty(queue)) {
        dequeue(queue); // 不断出队，释放节点
    }
    free(queue); // 释放队列结构体
}



int main() {
    Lqueue* queue = InitQueue();

    // 入队
    Enqueue(queue, 10);
    Enqueue(queue, 20);
    Enqueue(queue, 30);

    // 输出队列头部元素
    printf("队列头部元素: %d\n", front(queue));

    // 出队
    printf("出队元素: %d\n", dequeue(queue));
    printf("出队元素: %d\n", dequeue(queue));

    // 检查队列是否为空
    if (isEmpty(queue)) {
        printf("队列为空\n");
    } else {
        printf("队列不为空\n");
    }

    // 销毁队列
    destroyQueue(queue);

    return 0;
}
