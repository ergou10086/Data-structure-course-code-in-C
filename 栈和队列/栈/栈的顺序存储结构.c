#include <stdio.h>
#include <stdlib.h>

#define ElemType int //栈内元素数据类型

#define STACK_INIT_SIZE  8    //栈初始化大小
#define STACK_INC_SIZE   3    //栈增量的大小

//顺序栈结构
typedef struct SeqStack{
    ElemType *base;      //栈的基址 指向栈的空间
    int       capacity;  //栈的最大容量
    int       top;       //指向栈顶位置（可表示栈内元素个数）
}SeqStack;


// 初始化
int InitStack(SeqStack *s) {
    s->base = (ElemType *)malloc(sizeof (ElemType) * STACK_INC_SIZE);
    if(!s->base) return -1;  // 开辟内存失败
    //设置容量的初始化大小
    s->capacity = STACK_INC_SIZE;
    //设置栈顶的初始化指向
    s->top = 0;
    return 1;
}


// 栈扩容
int IncStack(SeqStack *s){
    //在原来栈空间基础上扩展STACK_INC_SIZE大小的空间
    ElemType *newbase = (ElemType *)realloc(s->base,sizeof(ElemType)*(s->capacity+STACK_INC_SIZE));
    //如果扩展失败，提示失败并退出
    if(newbase == NULL){
        printf("内存不足,无法申请空间.\n");
        return 0;
    }
    //将栈的基址指向扩展后的空间
    s->base = newbase;
    //将栈现容量设置为原栈容量+扩展的容量
    s->capacity += STACK_INC_SIZE;
    return 1;
}


// 入栈操作
int Push(SeqStack* s, ElemType e) {
    if (s->top >= s->capacity) {
        // 栈空间已满，需要扩容
        ElemType* newBase = (ElemType*)realloc(s->base, sizeof(ElemType) * (s->capacity + STACK_INC_SIZE));
        if (!newBase) return -1;  // 内存分配失败
        s->base = newBase;
        s->capacity += STACK_INC_SIZE;
    }
    s->base[s->top++] = e;
    return 0;
}


// 出栈操作
int Pop(SeqStack* s, ElemType* e) {
    if (s->top == 0) return -1;  // 栈为空，无法出栈
    *e = s->base[--s->top];
    return 0;
}


// 获取栈顶元素
int GetTop(SeqStack* s, ElemType* e) {
    if (s->top == 0) return -1;  // 栈为空，无栈顶元素
    *e = s->base[s->top - 1];
    return 0;
}


// 判断栈是否为空
int IsEmpty(SeqStack* s) {
    return s->top == 0;
}


// 销毁栈
int DestroyStack(SeqStack* s) {
    free(s->base);
    s->base = NULL;
    s->capacity = 0;
    s->top = 0;
    return 0;
}

// 测试示例
int main() {
    SeqStack stack;
    if (InitStack(&stack) == -1) {
        printf("栈初始化失败\n");
        return -1;
    }

    // 入栈操作测试
    for (int i = 1; i <= 10; i++) {
        if (Push(&stack, i) == -1) {
            printf("入栈失败\n");
            return -1;
        }
    }

    // 获取栈顶元素测试
    ElemType topElement;
    if (GetTop(&stack, &topElement) == 0) {
        printf("栈顶元素为: %d\n", topElement);
    }

    // 出栈操作测试
    ElemType poppedElement;
    if (Pop(&stack, &poppedElement) == 0) {
        printf("出栈元素为: %d\n", poppedElement);
    }

    // 判断栈是否为空测试
    if (IsEmpty(&stack)) {
        printf("栈为空\n");
    } else {
        printf("栈不为空\n");
    }


    // 销毁栈
    if (DestroyStack(&stack) == 0) {
        printf("栈已销毁\n");
    }

    return 0;
}

