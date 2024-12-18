#include <stdio.h>
#include <stdlib.h>

const int STACK_INIT_SIZE = 100;
const int STACK_INCREMENT = 10;

typedef struct {
    char *base;        // 栈底指针
    char *top;         // 栈顶指针
    int stack_size;    // 当前分配的栈可使用的最大存储量
} CharStack;

// 初始化栈
int InitStack(CharStack *s) {
    s->base = (char *)malloc(STACK_INIT_SIZE * sizeof(char));
    if (!s->base) return -1;  // 开辟内存失败
    s->top = s->base;    // 将栈顶指针top初始化为栈底指针base，表示栈目前为空
    s->stack_size = STACK_INIT_SIZE;
    return 0;
}

// 入栈
int Push(CharStack *s, char value) {
    if (s->top - s->base == s->stack_size) { // 如果栈满，增加空间
        char *new_base = (char *)realloc(s->base, (s->stack_size + STACK_INCREMENT) * sizeof(char));
        if (!new_base) return -1; // 内存分配失败
        s->base = new_base;
        s->top = s->base + s->stack_size;
        s->stack_size += STACK_INCREMENT;
    }
    *s->top++ = value;   // 入栈
    return 0;
}

// 出栈
int Pop(CharStack *s, char *value) {
    if (s->top == s->base) return -1;  // 栈空
    *value = *--s->top; // 出栈
    return 0;
}

// 检查栈是否为空
int IsEmpty(CharStack *s) {
    return s->top == s->base;
}

// 销毁栈
void DestroyStack(CharStack *s) {
    free(s->base);
    s->base = NULL;
    s->top = NULL;
    s->stack_size = 0;
}

// 括号匹配函数
int CheckParentheses(char *expression) {
    CharStack stack;
    if (InitStack(&stack) == -1) return -1;

    for (char *p = expression; *p; p++) {
        if (*p == '(' || *p == '{' || *p == '[') {
            Push(&stack, *p);
        } else if (*p == ')' || *p == '}' || *p == ']') {
            char top;
            if (Pop(&stack, &top) == -1) {
                DestroyStack(&stack);
                return 0; // 没有匹配的左括号
            }
            // 检查括号是否匹配
            if ((*p == ')' && top != '(') ||
                (*p == '}' && top != '{') ||
                (*p == ']' && top != '[')) {
                DestroyStack(&stack);
                return 0; // 括号不匹配
            }
        }
    }

    int result = IsEmpty(&stack); // 栈为空则匹配成功
    DestroyStack(&stack);
    return result;
}

int main() {
    char expression[100];
    printf("请输入一个表达式: ");
    fgets(expression, sizeof(expression), stdin);

    if (CheckParentheses(expression)) {
        printf("括号匹配!\n");
    } else {
        printf("括号不匹配!\n");
    }

    return 0;
}


