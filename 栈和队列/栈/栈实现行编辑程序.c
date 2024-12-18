#include <stdio.h>
#include <stdlib.h>

const int STACK_INIT_SIZE = 100;    // 栈存储空间的初始分配量
const int STACK_INCREMENT = 10;     // 栈存储空间发分配增量

typedef struct{
    int *base;        // 栈底指针
    int *top;         // 栈顶指针
    int stack_size;   // 当前分配的栈可使用的最大存储量
}SqStack;

// 初始化栈
int InitStack(SqStack *s){
    s->base = (int *)malloc(STACK_INIT_SIZE * sizeof(int));
    if(!s->base) return -1;  // 开辟内存失败
    s->top = s->base;    // 将栈顶指针top初始化为栈底指针base，表示栈目前为空
    s->stack_size = STACK_INIT_SIZE;
    return 0;
}


// 入栈
int Push(SqStack *s, int value){
    if (s->top - s->base == s->stack_size) { // 如果栈满，增加空间
        int *new_base = (int *)realloc(s->base, (s->stack_size + STACK_INCREMENT) * sizeof(int));
        if (!new_base) return -1; // 内存分配失败
        s->base = new_base;
        s->top = s->base + s->stack_size;
        s->stack_size += STACK_INCREMENT;
    }
    *s->top++ = value;   // *s->top = value;  *s->top++;
    return 0;
}


// 出栈
int Pop(SqStack *s){
    if(s->top == s->base) return -1;  // 栈空
    *--s->top; // 出栈
    return 0;
}


// 得到栈顶元素操作
int GetTopElement(SqStack *s){
    if(s->top == s->base) return -1;  // 栈空
    return *(s->top - 1);  // 返回栈顶元素
}


// 打印栈，并不需要pop
int PrintStack(SqStack *s) {
    if (s->top == s->base) return -1; // 栈空
    for (int i = 0; i < (s->top - s->base); i++) {
        printf("%d ", *(s->base + i)); // 从栈底开始打印
    }
    printf("\n"); // 打印结束后换行
    return 0;
}



// 销毁栈
void DestroyStack(SqStack *s) {
    free(s->base);
    s->base = NULL;
    s->top = NULL;
    s->stack_size = 0;
}


// 行编辑代码
void LineEdit(){
    SqStack stack;
    if (InitStack(&stack) != 0) {
        printf("Init ERROR\n");
        return;
    }
    char ch;
    while ((ch = getchar()) != EOF && ch != '\n') {
        if (ch=='#'){
            Pop(&stack);  // 退格，出栈
        }else if (ch == '@'){

        }
    }
}