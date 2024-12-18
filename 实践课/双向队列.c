#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

#define MAX_Q 10  // ������е��������

typedef struct {
    int *base;  // �洢Ԫ�صĶ�̬����
    int front;  // ��ͷָ��
    int rear;   // ��βָ��
} CircularQueue;

int InitCircularQueue(CircularQueue* cq){
    cq->base = (int *)malloc(MAX_Q * sizeof(int));  //��̬���鶯̬����
    if(!cq->base) return -1;  // ����ʧ��
    cq->front = cq->rear = 0;  // ��ʼ��ָ��
    return 0;
}

// �п�
bool isFull(CircularQueue* cq){
    return (cq->rear + 1) % MAX_Q == cq->front;
}

// ����
bool isEmpty(CircularQueue* cq){
    return  cq->front == cq->rear == 0;
}

// ���
int EnQueue(CircularQueue* cq, int val){
    if(isFull(cq)) return -1;
    cq->base[cq->rear] = val;
    cq->rear = (cq->rear + 1) % MAX_Q;
    printf("��ǰ��βԪ��%d\n", val);
    return 0;
}

// ����
void DeQueue(CircularQueue* cq, int *val){
    if(isEmpty(cq)) return;
    *val = cq->base[cq->front];
    cq->front = (cq->front + 1) % MAX_Q; // ���¶�ͷָ��
    printf("��ǰ����Ԫ��%d\n", *val);
}

// ���г���
int LengthCirQueue(CircularQueue* cq){
    int pos = 0;
    for(int i = cq->front; i != cq->rear; i = (i + 1) % MAX_Q){
        pos += 1;
    }
    return pos;
}


// �ͷŶ����ڴ�
void FreeQueue(CircularQueue *q) {
    free(q->base); // �ͷŶ�̬����
    q->base = NULL; // ָ���ÿ�
}

int main(void){
    CircularQueue cq;
    InitCircularQueue(&cq);

    printf("����:%d\n", isEmpty(&cq));  //�п�

    for(int i = 1; i <= 5; i++){
        EnQueue(&cq, i * 10);
    }

    int res;
    DeQueue(&cq, &res);

    printf("����Ϊ��%d\n", LengthCirQueue(&cq));
    FreeQueue(&cq);
    return 0;
}