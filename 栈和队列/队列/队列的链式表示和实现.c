#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

// ��������ڵ�
typedef struct Node {
    int data;               // �ڵ�����
    struct Node* next;      // ָ����һ���ڵ��ָ��
} QNode, *QueuePtr;

// ������нṹ��
typedef struct Queue {
    QueuePtr front;           // ָ�����ͷ����ָ��
    QueuePtr rear;            // ָ�����β����ָ��
} Lqueue;


// ��ʼ������
Lqueue *InitQueue(){
    Lqueue *queue = (Lqueue *) malloc(sizeof(Lqueue));
    if(!queue){
        printf("�ڴ����ʧ��\n");
        return NULL;
    }
    queue->front = NULL;
    queue->rear = NULL;
    return queue;
}


// ���
void Enqueue(Lqueue * queue, int value) {
    QNode *newNode = (QNode *) malloc(sizeof(QNode));
    if(!newNode){
        printf("�ڴ����ʧ��\n");
        return;
    }
    newNode -> data = value;
    newNode -> next = NULL;

    if(queue -> rear){
        queue -> rear -> next = newNode;   // ����ǰβ�ڵ��nextָ���½ڵ�
    }
    queue -> rear = newNode;  // ���¶���β����ʼ������ǰ��

    if (!queue->front) {
        queue->front = newNode;      // ��������ǿյģ�����ͷ��
    }
}


// ����
int dequeue(Lqueue* queue) {
    if(!queue -> front){
        printf("����Ϊ�գ��޷�����\n");
        return -1;
    }
    QNode *temp = queue -> front;
    int value = temp -> data;

    queue -> front = queue -> front -> next;  // �ȿչ�Ҫɾ���Ľڵ�

    if (queue -> rear == temp) {
        queue -> rear = queue -> front;  // �������Ϊ�գ�β��Ҳ����ΪNULL
    }
    free(temp);
    return value;
}


// ��ȡͷ�ڵ�Ԫ��
int front(Lqueue* queue) {
    if (!queue->front) {
        printf("����Ϊ��\n");
        return -1; // ���Է���һ����־��ʾ����Ϊ��
    }
    return queue->front->data;
}


// �п�
bool isEmpty(Lqueue* queue) {
    return queue->front == NULL;
}


// ���ٶ���
void destroyQueue(Lqueue* queue) {
    while (!isEmpty(queue)) {
        dequeue(queue); // ���ϳ��ӣ��ͷŽڵ�
    }
    free(queue); // �ͷŶ��нṹ��
}



int main() {
    Lqueue* queue = InitQueue();

    // ���
    Enqueue(queue, 10);
    Enqueue(queue, 20);
    Enqueue(queue, 30);

    // �������ͷ��Ԫ��
    printf("����ͷ��Ԫ��: %d\n", front(queue));

    // ����
    printf("����Ԫ��: %d\n", dequeue(queue));
    printf("����Ԫ��: %d\n", dequeue(queue));

    // �������Ƿ�Ϊ��
    if (isEmpty(queue)) {
        printf("����Ϊ��\n");
    } else {
        printf("���в�Ϊ��\n");
    }

    // ���ٶ���
    destroyQueue(queue);

    return 0;
}
