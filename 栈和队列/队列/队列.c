#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

#define MAX 100  // ���е��������

// ������нṹ��
typedef struct Queue {
    int items[MAX];
    int front;  // ��ͷ����
    int rear;   // ��β����
} queue;


// ��ʼ������
void InitQueue(queue *q){
    q -> front = 0;
    q -> rear = 0;
}


// �п�
bool isEmpty(queue *q){
    return q->front == -1;
}


// ����
bool isFull(queue *q){
    return q->rear == MAX - 1;
}


// ���
void EnQueue(queue *q, int value){
    if(isFull(q)){
        printf("�����������޷����\n");
        return;
    }
    if(isEmpty(q)){
        q -> front = 0;   // �������Ϊ�գ�frontָ��0
    }
    q -> rear++;
    q -> items[q -> rear] = value;
    printf("�����: %d\n", value);
}


// ����
int DeQueue(queue *q){
    if (isEmpty(q)) {
        printf("����Ϊ�գ��޷�����\n");
        return -1;  // ����-1��ʾ����Ϊ��
    }
    int item = q->items[q->front];

    if(q -> front == q -> rear){
        q -> front = q -> rear = -1;
    }else{
        q -> front++;
    }
    printf("�ѳ���: %d\n", item);
    return item;
}


// �鿴��ͷԪ��
int peek(queue* q) {
    if (isEmpty(q)) {
        printf("����Ϊ�գ��޷��鿴��ͷ\n");
        return -1;
    }
    return q->items[q->front];
}


// ��ӡ����
void display(queue* q) {
    if (isEmpty(q)) {
        printf("����Ϊ��\n");
        return;
    }
    printf("����Ԫ��: ");
    for (int i = q->front; i <= q->rear; i++) {
        printf("%d ", q->items[i]);
    }
    printf("\n");
}

// ������
int main() {
    queue q;
    InitQueue(&q);

    EnQueue(&q, 10);
    EnQueue(&q, 20);
    EnQueue(&q, 30);

    display(&q);

    printf("��ͷԪ��: %d\n", peek(&q));

    DeQueue(&q);
    display(&q);

    DeQueue(&q);
    display(&q);

    return 0;
}