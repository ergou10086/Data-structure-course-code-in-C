#include <stdio.h>
#include <stdlib.h>

const int STACK_INIT_SIZE = 100;    // 栈存储空间的初始分配量
const int STACK_INCREMENT = 10;     // 栈存储空间的增加量

typedef struct{
    int *base;        // 栈底指针
    int *top;         // 栈顶指针
    int stack_size;   // 当前分配的栈可使用的最大存储量
} SqStack;

// 初始化栈
int InitStack(SqStack *s) {
    s->base = (int *)malloc(STACK_INIT_SIZE * sizeof(int));
    if (!s->base) return -1;  // 开辟内存失败
    s->top = s->base;          // 栈初始化为空
    s->stack_size = STACK_INIT_SIZE;
    return 0;
}

// 入栈
int Push(SqStack *s, int value) {
    if (s->top - s->base == s->stack_size) { // 如果栈满，增加空间
        int *new_base = (int *)realloc(s->base, (s->stack_size + STACK_INCREMENT) * sizeof(int));
        if (!new_base) return -1; // 内存分配失败
        s->base = new_base;
        s->top = s->base + s->stack_size;
        s->stack_size += STACK_INCREMENT;
    }
    *s->top++ = value; // 入栈
    return 0;
}

// 出栈
int Pop(SqStack *s, int *value) {
    if (s->top == s->base) return -1;  // 栈空
    *value = *--s->top; // 出栈
    return 0;
}

// 销毁栈
void DestroyStack(SqStack *s) {
    free(s->base);
    s->base = NULL;
    s->top = NULL;
    s->stack_size = 0;
}



// 进制转换函数,十转其他
void DecimalToBase(int number, int base) {
    SqStack stack;
    if (InitStack(&stack) != 0) {
        printf("Init ERROR\n");
        return;
    }

    while(number > 0){
        int mod = number % base;  // 计算余数
        Push(&stack, mod);  // 入栈
        number /= base;    // 更新数字
    }

    int value;
    while(Pop(&stack, &value) == 0){
        // 依次弹出栈中元素
        if(base == 16){
            printf("%X", value); // 十六进制格式
        }else {
            printf("%d", value); // 其他进制格式
        }
    }
    printf("\n");

    DestroyStack(&stack); // 销毁栈
}





// 主函数
int main() {
    int number, base;
    printf("请输入一个十进制整数：");
    scanf("%d", &number);
    printf("请输入目标进制（2、8、10、16）：");
    scanf("%d", &base);

    if (base == 2 || base == 8 || base == 10 || base == 16) {
        DecimalToBase(number, base); // 进行进制转换
    } else {
        printf("不支持的进制\n");
    }

    return 0;
}