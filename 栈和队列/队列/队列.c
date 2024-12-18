#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

#define MAX 100  // 队列的最大容量

// 定义队列结构体
typedef struct Queue {
    int items[MAX];
    int front;  // 队头索引
    int rear;   // 队尾索引
} queue;


// 初始化队列
void InitQueue(queue *q){
    q -> front = 0;
    q -> rear = 0;
}


// 判空
bool isEmpty(queue *q){
    return q->front == -1;
}


// 判满
bool isFull(queue *q){
    return q->rear == MAX - 1;
}


// 入队
void EnQueue(queue *q, int value){
    if(isFull(q)){
        printf("队列已满，无法入队\n");
        return;
    }
    if(isEmpty(q)){
        q -> front = 0;   // 如果队列为空，front指向0
    }
    q -> rear++;
    q -> items[q -> rear] = value;
    printf("已入队: %d\n", value);
}


// 出队
int DeQueue(queue *q){
    if (isEmpty(q)) {
        printf("队列为空，无法出队\n");
        return -1;  // 返回-1表示队列为空
    }
    int item = q->items[q->front];

    if(q -> front == q -> rear){
        q -> front = q -> rear = -1;
    }else{
        q -> front++;
    }
    printf("已出队: %d\n", item);
    return item;
}


// 查看队头元素
int peek(queue* q) {
    if (isEmpty(q)) {
        printf("队列为空，无法查看队头\n");
        return -1;
    }
    return q->items[q->front];
}


// 打印队列
void display(queue* q) {
    if (isEmpty(q)) {
        printf("队列为空\n");
        return;
    }
    printf("队列元素: ");
    for (int i = q->front; i <= q->rear; i++) {
        printf("%d ", q->items[i]);
    }
    printf("\n");
}

// 主函数
int main() {
    queue q;
    InitQueue(&q);

    EnQueue(&q, 10);
    EnQueue(&q, 20);
    EnQueue(&q, 30);

    display(&q);

    printf("队头元素: %d\n", peek(&q));

    DeQueue(&q);
    display(&q);

    DeQueue(&q);
    display(&q);

    return 0;
}