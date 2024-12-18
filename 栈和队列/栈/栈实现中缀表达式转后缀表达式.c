#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_SIZE 100

// 操作符的优先级比较
int precedence(char op) {
    if (op == '(') return 0;
    if (op == '+' || op == '-') return 1;
    if (op == '*' || op == '/') return 2;
    return -1;
}

// 顺序栈结构，用于暂存操作符
typedef struct SeqStack {
    char *base;
    int top;
    int capacity;
} SeqStack;

// 初始化栈
void InitStack(SeqStack *s) {
    s->base = (char *)malloc(MAX_SIZE * sizeof(char));
    if (!s->base) {
        printf("内存分配失败\n");
        exit(1);
    }
    s->top = 0;
    s->capacity = MAX_SIZE;
}

// 入栈操作
void Push(SeqStack *s, char e) {
    if (s->top == s->capacity) {
        printf("栈已满\n");
        return;
    }
    s->base[s->top++] = e;
}

// 出栈操作
char Pop(SeqStack *s) {
    if (s->top == 0) {
        printf("栈为空\n");
        return '\0';
    }
    return s->base[--s->top];
}

// 获取栈顶元素
char GetTop(SeqStack *s) {
    if (s->top == 0) {
        return '\0';
    }
    return s->base[s->top - 1];
}

// 判断栈是否为空
int IsEmpty(SeqStack *s) {
    return s->top == 0;
}

// 中缀表达式转后缀表达式的函数
void infixToPostfix(char *infix, char *postfix) {
    SeqStack s;
    InitStack(&s);
    // i 和 j 分别用于遍历中缀表达式和构建后缀表达式
    int i, j;
    i = j = 0;
    int len = strlen(infix);

    // 扫描中缀表达式并转换
    for (i = 0; i < len; i++) {
        char ch = infix[i];
        // 如果当前字符是数字或者字母，也就是操作数，直接将其添加到后缀表达式数组中，索引 j 后移一位。
        if ((ch >= '0' && ch <= '9') || (ch >= 'a' && ch <= 'z')) {
            postfix[j++] = ch;
        // 当遇到左括号时，直接将其压入栈中，等待后续与之匹配的右括号出现。
        } else if (ch == '(') {
            Push(&s, ch);
        // 遇到右括号时
        } else if (ch == ')') {
            // 将栈中元素依次弹出并添加到后缀表达式中
            while (!IsEmpty(&s) && GetTop(&s)!= '(') {
                postfix[j++] = Pop(&s);
            }
            // 直到遇到与之匹配的左括号，然后将左括号弹出（但不添加到后缀表达式中）
            if (!IsEmpty(&s) && GetTop(&s) == '(') {
                Pop(&s);
            }
        } else {
            // 对于普通操作符，要比较其与栈顶操作符的优先级，只要栈不为空且栈顶操作符的优先级大于等于当前操作符的优先级，就将栈顶操作符弹出并添加到后缀表达式中，然后再将当前操作符入栈
            while (!IsEmpty(&s) && precedence(GetTop(&s)) >= precedence(ch)) {
                postfix[j++] = Pop(&s);
            }
            Push(&s, ch);
        }
    }

    // 栈中可能还剩余一些操作符，将它们依次弹出并添加到后缀表达式末尾
    while (!IsEmpty(&s)) {
        postfix[j++] = Pop(&s);
    }
    postfix[j] = '\0';
}

int main() {
    char infix[MAX_SIZE] = "3+(4*2-1)";
    char postfix[MAX_SIZE];
    infixToPostfix(infix, postfix);
    printf("中缀表达式: %s\n", infix);
    printf("后缀表达式: %s\n", postfix);
    return 0;
}
