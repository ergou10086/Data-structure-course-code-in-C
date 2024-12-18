#include <stdio.h>
#include <stdlib.h>

const int STACK_INIT_SIZE = 100;    // 栈存储空间的初始分配量
const int STACK_INCREMENT = 10;     // 栈存储空间发分配增量

typedef struct {
    int* data;         // 存储栈的数组
    int top;           // 栈顶索引
    int bottom;        // 栈底索引
    int SqSize;      // 栈的大小
} DoubleStack;


// 初始化双向栈
DoubleStack* initDoubleStack() {
    DoubleStack* stack = (DoubleStack*)malloc(sizeof(DoubleStack));
    stack->data = (int*)malloc(STACK_INIT_SIZE * sizeof(int));
    stack->top = -1;        // top指针初始为-1
    stack->bottom = STACK_INIT_SIZE; // bottom指针初始为数组的末尾
    stack->SqSize = STACK_INIT_SIZE; // 栈的最大大小
    return stack;
}

// top入栈
void pushTop(DoubleStack* stack, int data) {
    // 栈满了
    if (stack->top + 1 == stack->bottom) {
        return;
    }
    stack->data[++stack->top] = data;
}

// bottom入栈
void pushBottom(DoubleStack* stack, int data){
    if (stack->bottom - stack->top <= 1) {
        return;
    }
    stack->data[--stack->bottom] = data; // 插入数据并更新栈底
}

// top出栈，并且返回值
int popTop(DoubleStack* stack) {
    if (stack->top == -1) {
        printf("栈空，无法从栈顶出栈！\n");
        return -1;
    }
    return stack->data[stack->top--];
}

// bottom出栈，并返回
int popBottom(DoubleStack* stack){
    if(stack->bottom == -1){
        printf("栈空，无法从栈底出栈！\n");
        return -1;
    }
    return stack->data[stack->bottom++];
}

// 判满
int isFull(DoubleStack* stack) {
    return stack->top - stack->bottom == -1;
}

// 判空
int isEmpty(DoubleStack* stack) {
    return stack->top == -1 && stack->bottom == stack->SqSize;
}

// 查看栈顶元素
int peekTop(DoubleStack* stack){
    if(isEmpty(stack)){
        printf("栈空\n");
        return -1;
    }
    return stack->data[stack->top];
}

// 查看栈底元素
int peekBottom(DoubleStack* stack){
    if(isEmpty(stack)){
        printf("栈空\n");
        return -1;
    }
    return stack->data[stack->bottom];
}

// 释放栈
void freeStack(DoubleStack* stack) {
    free(stack->data);
    free(stack);
}


int main(void) {
    DoubleStack* stack = initDoubleStack();

    pushTop(stack, 10);
    pushTop(stack, 20);
    pushTop(stack, 30);
    pushBottom(stack, 40);
    pushBottom(stack, 50);

    printf("栈顶出栈: %d\n", popTop(stack));

    printf("栈顶元素: %d\n", peekTop(stack));

    freeStack(stack);
    return 0;
}