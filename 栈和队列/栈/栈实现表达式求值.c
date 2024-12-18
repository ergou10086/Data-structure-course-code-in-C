#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>

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
int Pop(SqStack *s, int *value){
    if(s->top == s->base) return -1;  // 栈空
    *value = *--s->top; // 出栈
    return 0;
}


// 得到栈顶元素操作
int GetTopElement(SqStack *s){
    if(s->top == s->base) return -1;  // 栈空
    return *(s->top - 1);  // 返回栈顶元素
}

// 判断运算符优先级
int precedence(char op) {
    switch (op) {
        case '+':
        case '-':
            return 1;
        case '*':
        case '/':
            return 2;
        default:
            return 0;
    }
}

// 执行运算
int apply_operator(int a, int b, char op) {
    switch (op) {
        case '+': return a + b;
        case '-': return a - b;
        case '*': return a * b;
        case '/':
            if(b == 0){
                return 0;
            }else{
                return a / b;
            }
        default: return 0;
    }
}


// 求表达式值
int evaluate_expression(const char *expression) {
    SqStack values, operators;
    // 两个栈，一个存运算符，一个存操作数
    InitStack(&values);
    InitStack(&operators);

    for (int i = 0; expression[i] != '\0'; i++) {
        // 跳过空格
        if (isspace(expression[i])) continue;

        // 数字弹出
        if(isdigit(expression[i])){
            int value = 0;
            while(isdigit(expression[i])){
                value = value * 10 + (expression[i] - '0');
                i++;
            }
            i--; // 回退一个字符
            Push(&values, value);
        }

        // 运算符处理
        else if (expression[i] == '+' || expression[i] == '-' || expression[i] == '*' || expression[i] == '/') {
            // 运算符栈不空，且栈顶元素优先级大于当前存入的
            while(operators.top > operators.base && precedence(GetTopElement(&operators)) >= precedence(expression[i])){
                int a, b;
                Pop(&values, &b);
                Pop(&values, &a);
                char op = GetTopElement(&operators);
                Pop(&operators, NULL);
                int result = apply_operator(a, b, op);
                Push(&values, result);
            }
            Push(&operators, expression[i]);
        }
    }

    // 处理剩余的运算符
    while (operators.top > operators.base) {
        int b, a;
        Pop(&values, &b);
        Pop(&values, &a);
        char op = GetTopElement(&operators);
        Pop(&operators, NULL);
        int result = apply_operator(a, b, op);
        Push(&values, result);
    }

    // 返回最终的结果
    int final_result;
    Pop(&values, &final_result);
    return final_result;

}


// 主函数
int main() {
    const char *expression = "1 + 2 * 3 - 16 / 2";
    int result = evaluate_expression(expression);
    printf("Result: %d\n", result); // 应该输出 -1
    return 0;
}