#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

#define MAX_C 10  // 定义队列的最大容量

typedef struct {
    int *base;  // 存储队列元素的动态数组
    int front;  // 队头指针
    int rear;   // 队尾指针
} CircularQueue;

// 初始化一个循环队列
int InitQueue(CircularQueue *q) {
    q->base = (int *) malloc(MAX_C * sizeof(int)); // 动态分配内存
    if (!q->base) return -1; // 分配失败
    q->front = q->rear = 0; // 初始化指针
    return 0; // 成功
}

// 判空
bool isEmpty(CircularQueue *q) {
    return q->front == q->rear; // 队头和队尾相等时为空
}

// 判满
bool isFull(CircularQueue *q) {
    return (q->rear + 1) % MAX_C == q->front; // 满的条件
}

// 获取循环队列的长度
int LengthQueue(CircularQueue *q) {
    return (q->rear - q->front + MAX_C) % MAX_C; // 计算长度
}

// 插入元素val为队列新的队尾元素
int Enqueue(CircularQueue *q, int val) {
    if (isFull(q)) return -1; // 队列满，无法插入
    q->base[q->rear] = val; // 插入元素
    q->rear = (q->rear + 1) % MAX_C; // 更新队尾指针，rear指针向后移一位置
    return 0; // 成功
}

// 弹出队头元素，并返回其值
int Dequeue(CircularQueue *q, int *val) {
    if (isEmpty(q)) return -1; // 队列空，无法弹出
    *val = q->base[q->front]; // 获取队头元素
    q->front = (q->front + 1) % MAX_C; // 更新队头指针，front指针向后移一位置
    return 0; // 成功
}

// 获取队头元素的值
int Front(CircularQueue *q, int *val) {
    if (isEmpty(q)) return -1; // 队列空，无法获取
    *val = q->base[q->front]; // 获取队头元素
    return 0; // 成功
}

// 查找循环队列中第i个元素
int FindIndex(CircularQueue *q, int index) {
    // 确保索引有效
    int length = LengthQueue(q);
    if (index < 0 || index >= length) {
        return -1; // 索引无效
    }

    // 计算要访问的元素的实际位置
    int actualIndex = (q->front + index) % MAX_C;
    return q->base[actualIndex]; // 返回第 index 个元素
}

// 按值查找
int FindValue(CircularQueue *q, int value) {
    int length = LengthQueue(q);

    for (int i = 0; i < length; i++) {
        // 计算实际索引
        int actualIndex = (q->front + i) % MAX_C;
        if (q->base[actualIndex] == value) {
            return i; // 返回值的索引
        }
    }

    return -1; // 未找到
}

// 清空队列
void ClearQueue(CircularQueue *q) {
    q->front = q->rear = 0; // 重置指针
}

// 释放队列内存
void FreeQueue(CircularQueue *q) {
    free(q->base); // 释放动态数组
    q->base = NULL; // 指针置空
}

// 显示队列中的所有元素
void DisplayQueue(CircularQueue *q) {
    if (isEmpty(q)) {
        printf("Queue is empty!\n");
        return;
    }
    printf("Queue elements: ");
    // 循环队列里实现+1，就是rear = (rear + 1) % MAX_C
    for (int i = q->front; i != q->rear; i = (i + 1) % MAX_C) {
        printf("%d ", q->base[i]); // 打印队列中的每个元素
    }
    printf("\n");
}

// 主函数示例
int main() {
    CircularQueue q;
    if (InitQueue(&q) != 0) {
        printf("Failed to initialize queue.\n");
        return -1;
    }

    printf("queue is Empty?:%d\n", isEmpty(&q));  //判空

    Enqueue(&q, 10);
    Enqueue(&q, 20);
    Enqueue(&q, 30);
    Enqueue(&q, 40);
    Enqueue(&q, 50);

    DisplayQueue(&q); // 显示队列

    int n = 4;
    printf("the n%d element is %d\n", n, FindIndex(&q, n));
    int p = 20;
    printf("the %d s index in %d\n", p, FindValue(&q, p));

    int val;
    if (Dequeue(&q, &val) == 0) {
        printf("Dequeued: %d\n", val);
    }

    DisplayQueue(&q); // 再次显示队列

    if (Front(&q, &val) == 0) {
        printf("Front element: %d\n", val);
    }

    // 插入更多元素以测试满的情况
    Enqueue(&q, 60);
    Enqueue(&q, 70);
    Enqueue(&q, 80);
    Enqueue(&q, 90);
    Enqueue(&q, 100); // 队列满

    DisplayQueue(&q); // 显示队列

    printf("queue is Full?:%d\n", isFull(&q));  //判满

    // 清理和释放内存
    FreeQueue(&q);
    return 0;
}
