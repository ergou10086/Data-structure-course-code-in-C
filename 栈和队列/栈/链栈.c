#include <stdio.h>
#include <stdlib.h>

typedef int ElemType;

/*栈的链式存储结构*/

// 构造节点
typedef struct StackNode{
    ElemType data;
    struct StackNode *next;
}StackNode, *LinkStackPrt;

// 构造链栈
typedef struct LinkStack{
    LinkStackPrt top;
    int count;
}LinkStack;


// 初始化链栈
void InitLinkStack(LinkStack *s) {
    s->top = NULL;
    s->count = 0;
}


// 入栈操作
void Push(LinkStack *s, ElemType e) {
    LinkStackPrt newNode = (LinkStackPrt)malloc(sizeof(StackNode));
    if (newNode == NULL) {
        printf("内存分配失败\n");
        exit(EXIT_FAILURE);
    }
    // 将传入的元素值 e 赋给新节点的 data 域
    newNode->data = e;
    // 让新节点的 next 指针指向当前栈顶节点（即 s->top）
    newNode->next = s->top;
    // 将新节点设置为栈顶节点，计数器++
    s->top = newNode;
    s->count++;
}


// 出栈操作
void Pop(LinkStack *s, ElemType *e) {
    // s->count 是否为 0 来确定栈是否为空
    if (s->count == 0) {
        printf("栈为空，无法出栈\n");
        return;
    }
    // 定义一个临时指针 p 指向当前栈顶节点（即 s->top）
    LinkStackPrt p = s->top;
    *e = p->data;
    // 栈顶指针 s->top 指向当前栈顶节点的下一个节点
    s->top = p->next;
    // 释放掉原栈顶节点，count--
    free(p);
    s->count--;
}


// 获取栈顶元素
void GetTop(LinkStack *s, ElemType *e) {
    if (s->count == 0) {
        printf("栈为空，无栈顶元素\n");
        return;
    }
    *e = s->top->data;
}


// 判断栈是否为空
int IsEmpty(LinkStack *s) {
    return s->count == 0;
}


// 销毁链栈
void DestroyLinkStack(LinkStack *s) {
    LinkStackPrt p;
    while (s->top!= NULL) {
        p = s->top;
        s->top = s->top->next;
        free(p);
    }
    s->count = 0;
}



// 测试示例
int main() {
    LinkStack stack;
    InitLinkStack(&stack);

    // 入栈操作测试
    Push(&stack, 1);
    Push(&stack, 2);
    Push(&stack, 3);

    // 获取栈顶元素测试
    ElemType topElement;
    GetTop(&stack, &topElement);
    printf("栈顶元素为: %d\n", topElement);

    // 出栈操作测试
    ElemType poppedElement;
    Pop(&stack, &poppedElement);
    printf("出栈元素为: %d\n", poppedElement);

    // 判断栈是否为空测试
    if (IsEmpty(&stack)) {
        printf("栈为空\n");
    } else {
        printf("栈不为空\n");
    }

    // 销毁链栈
    DestroyLinkStack(&stack);
    return 0;
}
