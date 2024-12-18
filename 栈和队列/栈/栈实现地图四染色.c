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
int Pop(SqStack *s, int *value){
    if(s->top == s->base) return -1;  // 栈空
    *value = *--s->top; // 出栈
    return 0;
}


int checkColor(int region, int colors[], int adj[100][100], int num_regions){
    for(int i = 0; i < num_regions; i++){
        if (adj[region][i] == 1 && colors[i] == colors[region]) {
            return 0;  // 相同颜色不合理
        }
    }
    return 1;
}



// 四地图染色
int FourColoring(int adj[100][100], int num_regions) {
    int colors[100]; // 存储每个区域的颜色
    for (int i = 0; i < num_regions; i++) {
        colors[i] = -1; // 初始化颜色为-1（未着色）
    }

    SqStack stack;
    InitStack(&stack);

    int region = 0; // 从第一个区域开始
    int color = 0;  // 从颜色0开始

    while(region < num_regions){
        while (color < 4) {     // 试探四种颜色
            colors[region] = color;     // 上色
            if(checkColor(region, colors, adj, num_regions)){
                Push(&stack, region);   // 入栈当前区域
                region++;   // 处理下个区域
                color = 0;  // 重置颜色
                break;
            }
            color++;
        }

        // 如果所有颜色都试过，依旧无法上色，需要取出上一个区域的颜色，重新尝试
        if(color == 4){
            if(Pop(&stack, &region) == -1){
                return -1;
            }
            color = colors[region]; // 取出上一个区域的颜色
            colors[region] = -1; // 重置当前区域颜色
            color++; // 尝试下一种颜色
        }

        // 输出结果
        printf("区域颜色分配：\n");
        for (int i = 0; i < num_regions; i++) {
            printf("区域 %d: 颜色 %d\n", i, colors[i]);
        }
        return 0;

    }
}



int main(void){
    int num_regions; // 区域数量
    int adj[100][100] = {0}; // 邻接矩阵

    scanf("%d", &num_regions);

    for (int i = 0; i < num_regions; i++) {
        for (int j = 0; j < num_regions; j++) {
            scanf("%d", &adj[i][j]); // 输入邻接矩阵
        }
    }

    // 调用四染色函数
    FourColoring(adj, num_regions);

    return 0;
}