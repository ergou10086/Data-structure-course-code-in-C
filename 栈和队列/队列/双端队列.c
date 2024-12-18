#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>

#define MAX_SIZE 20

//双端队列可以使用数组或链表实现，使用双链表应该比较简单，但这里使用循环数组来实现双端队列的增删改查等操作
typedef struct DoubleQueue {
    int front;//头指针
    int rear;//尾指针
    int numofele;//队列中的元素数量
    int arr[MAX_SIZE];//假设队列中只存储非负整数，最大容量为MAX_SIZE
}DoubleQueue;

//创建队列
DoubleQueue* CreatQueue() {
    DoubleQueue* q = (DoubleQueue*)malloc(sizeof(DoubleQueue));
    if (q == NULL) {
        perror("malloc");
        return NULL;
    }
    //假设队列的队头入队和队尾入队都是从数组下标为0处开始
    q->front = q->rear = -1;
    q->numofele = 0;
    return q;
}

//清空队列
void ClearQueue(DoubleQueue* q) {
    if (q == NULL) {
        printf("队列不存在\n");
        return;
    }
    //清空队列时，只需要改变头尾指针和队列中元素的数量即可
    q->front = q->rear = -1;
    q->numofele = 0;
}

//销毁队列
void DestoryQueue(DoubleQueue* q) {
    if (q == NULL) {
        printf("队列不存在\n");
        return;
    }
    //由于队列只使用了一次动态内存分配，所以直接free
    free(q);
    q = NULL;
}

//判断队列是否为空
bool IsEmpty(DoubleQueue* q) {
    if (q == NULL) {
        printf("队列不存在\n");
        return true;//返回true为了防止在队列为空时的操作引用空指针
    }
    return q->numofele == 0;
}

//判断队列是否为满
bool IsFull(DoubleQueue* q) {
    if (q == NULL) {
        printf("队列不存在\n");
        return true;//为了防止在队列不满情况下对空指针的操作
    }
    return q->numofele == MAX_SIZE;
}

//返回队头元素
int GetHead(DoubleQueue* q) {
    if (q == NULL) {
        printf("队列不存在\n");
        return -1;//假设队列中存储非负整数，返回-1表示错误
    }
    if (IsEmpty(q)) {
        printf("队列为空，不存在队头元素\n");
        return -1;
    }
    return q->arr[q->front];
}

//返回队尾元素
int GetTail(DoubleQueue* q) {
    if (q == NULL) {
        printf("队列不存在\n");
        return -1;//假设队列中存储非负整数，返回-1表示错误
    }
    if (IsEmpty(q)) {
        printf("队列为空，不存在队尾元素\n");
        return -1;
    }
    return q->arr[q->rear];
}

//获得从队头入队的下标
int GetHeadIndex(DoubleQueue* q, int size) {
    if (IsEmpty(q)) {
        q->rear = 0;//如果从对头入队的是第一个元素，则需要将队头队尾指针都设为0
        return 0;
    }
    if (q->front - 1 < 0) {
        return (q->front - 1) + size;
    }
    else {
        return q->front - 1;
    }
}

//从队头入队
void EnqueueFromHead(DoubleQueue* q, int k) {
    if (q == NULL) {
        printf("队列不存在\n");
        return;
    }
    if (IsFull(q)) {
        printf("队列已满，无法入队\n");
        return;
    }
    q->front = GetHeadIndex(q, MAX_SIZE);
    q->numofele++;
    q->arr[q->front] = k;
}

//得到从队尾入队的下标
int GetTailIndex(DoubleQueue* q, int size) {
    if (IsEmpty(q)) {
        q->front = 0;
        return 0;
    }
    return (q->rear + 1) % size;
}

//从队尾入队
void EnqueueFromTail(DoubleQueue* q, int k) {
    if (q == NULL) {
        printf("队列不存在\n");
        return;
    }
    if (IsFull(q)) {
        printf("队列已满，无法入队\n");
        return;
    }
    q->rear = GetTailIndex(q, MAX_SIZE);
    q->numofele++;
    q->arr[q->rear] = k;
}

//从队头出队
int DequeueFromHead(DoubleQueue* q) {
    if (q == NULL) {
        printf("队列不存在\n");
        return -1;
    }
    if (IsEmpty(q)) {
        printf("队列为空，无法出队\n");
        return -1;
    }
    q->numofele--;
    int ret = q->arr[q->front];
    q->front = (q->front + 1) % MAX_SIZE;
    return ret;
}

//从队尾出队
int DequeueFromTail(DoubleQueue* q) {
    if (q == NULL) {
        printf("队列不存在\n");
        return -1;
    }
    if (IsEmpty(q)) {
        printf("队列为空，无法出队\n");
        return -1;
    }
    int ret = q->arr[q->rear];
    q->numofele--;
    if (q->rear - 1 < 0) {
        q->rear = q->rear - 1 + MAX_SIZE;
    }
    else {
        q->rear = q->rear - 1;
    }
    return ret;
}

//从队头开始打印队列数据
void Print(DoubleQueue* q) {
    if (q == NULL) {
        printf("队列不存在\n");
        return;
    }
    if (IsEmpty(q)) {
        printf("队列为空，无法打印\n");
        return;
    }
    int count = q->numofele;
    int p = q->front;
    while (count--) {
        printf("%d ", q->arr[p]);
        p = (p + 1) % MAX_SIZE;
    }
    printf("\n--------------------------\n");
}

int main() {

    DoubleQueue* q = CreatQueue();

    //从队头入队10个元素
    for (int i = 0; i < 10; i++) {
        EnqueueFromHead(q, i);
    }
    Print(q);

    for (int i = 10; i < 20; i++) {
        EnqueueFromTail(q, i);
    }
    Print(q);

    printf("从队头删除的元素是 %d\n", DequeueFromHead(q));
    Print(q);
    printf("从队尾删除的元素是：%d\n", DequeueFromTail(q));
    Print(q);

    printf("队头元素是：%d\n", GetHead(q));
    printf("队尾元素是：%d\n", GetTail(q));

    return 0;
}
