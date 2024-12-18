#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

#define MAX_Q 10  // 定义队列的最大容量

typedef struct {
    int *base;  // 存储元素的动态数组
    int front;  // 队头指针
    int rear;   // 队尾指针
} CircularQueue;

int InitCircularQueue(CircularQueue* cq){
    cq->base = (int *)malloc(MAX_Q * sizeof(int));  //动态数组动态分配
    if(!cq->base) return -1;  // 分配失败
    cq->front = cq->rear = 0;  // 初始化指针
    return 0;
}

// 判空
bool isFull(CircularQueue* cq){
    return (cq->rear + 1) % MAX_Q == cq->front;
}

// 判满
bool isEmpty(CircularQueue* cq){
    return  cq->front == cq->rear == 0;
}

// 入队
int EnQueue(CircularQueue* cq, int val){
    if(isFull(cq)) return -1;
    cq->base[cq->rear] = val;
    cq->rear = (cq->rear + 1) % MAX_Q;
    printf("当前队尾元素%d\n", val);
    return 0;
}

// 出队
void DeQueue(CircularQueue* cq, int *val){
    if(isEmpty(cq)) return;
    *val = cq->base[cq->front];
    cq->front = (cq->front + 1) % MAX_Q; // 更新队头指针
    printf("当前出队元素%d\n", *val);
}

// 队列长度
int LengthCirQueue(CircularQueue* cq){
    int pos = 0;
    for(int i = cq->front; i != cq->rear; i = (i + 1) % MAX_Q){
        pos += 1;
    }
    return pos;
}


// 释放队列内存
void FreeQueue(CircularQueue *q) {
    free(q->base); // 释放动态数组
    q->base = NULL; // 指针置空
}

int main(void){
    CircularQueue cq;
    InitCircularQueue(&cq);

    printf("空吗:%d\n", isEmpty(&cq));  //判空

    for(int i = 1; i <= 5; i++){
        EnQueue(&cq, i * 10);
    }

    int res;
    DeQueue(&cq, &res);

    printf("长度为：%d\n", LengthCirQueue(&cq));
    FreeQueue(&cq);
    return 0;
}