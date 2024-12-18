#include <stdio.h>
#include <stdlib.h>

const int STACK_INIT_SIZE = 100;    // ջ�洢�ռ�ĳ�ʼ������
const int STACK_INCREMENT = 10;     // ջ�洢�ռ䷢��������

typedef struct {
    int* data;         // �洢ջ������
    int top;           // ջ������
    int bottom;        // ջ������
    int SqSize;      // ջ�Ĵ�С
} DoubleStack;


// ��ʼ��˫��ջ
DoubleStack* initDoubleStack() {
    DoubleStack* stack = (DoubleStack*)malloc(sizeof(DoubleStack));
    stack->data = (int*)malloc(STACK_INIT_SIZE * sizeof(int));
    stack->top = -1;        // topָ���ʼΪ-1
    stack->bottom = STACK_INIT_SIZE; // bottomָ���ʼΪ�����ĩβ
    stack->SqSize = STACK_INIT_SIZE; // ջ������С
    return stack;
}

// top��ջ
void pushTop(DoubleStack* stack, int data) {
    // ջ����
    if (stack->top + 1 == stack->bottom) {
        return;
    }
    stack->data[++stack->top] = data;
}

// bottom��ջ
void pushBottom(DoubleStack* stack, int data){
    if (stack->bottom - stack->top <= 1) {
        return;
    }
    stack->data[--stack->bottom] = data; // �������ݲ�����ջ��
}

// top��ջ�����ҷ���ֵ
int popTop(DoubleStack* stack) {
    if (stack->top == -1) {
        printf("ջ�գ��޷���ջ����ջ��\n");
        return -1;
    }
    return stack->data[stack->top--];
}

// bottom��ջ��������
int popBottom(DoubleStack* stack){
    if(stack->bottom == -1){
        printf("ջ�գ��޷���ջ�׳�ջ��\n");
        return -1;
    }
    return stack->data[stack->bottom++];
}

// ����
int isFull(DoubleStack* stack) {
    return stack->top - stack->bottom == -1;
}

// �п�
int isEmpty(DoubleStack* stack) {
    return stack->top == -1 && stack->bottom == stack->SqSize;
}

// �鿴ջ��Ԫ��
int peekTop(DoubleStack* stack){
    if(isEmpty(stack)){
        printf("ջ��\n");
        return -1;
    }
    return stack->data[stack->top];
}

// �鿴ջ��Ԫ��
int peekBottom(DoubleStack* stack){
    if(isEmpty(stack)){
        printf("ջ��\n");
        return -1;
    }
    return stack->data[stack->bottom];
}

// �ͷ�ջ
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

    printf("ջ����ջ: %d\n", popTop(stack));

    printf("ջ��Ԫ��: %d\n", peekTop(stack));

    freeStack(stack);
    return 0;
}