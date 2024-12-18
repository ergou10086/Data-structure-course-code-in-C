#include <stdio.h>
#include <stdlib.h>

const int STACK_INIT_SIZE = 100;    // 栈存储空间的初始分配量
const int STACK_INCREMENT = 10;     // 栈存储空间发分配增量

// 位置的结构体
typedef struct {
    int x; // x坐标
    int y; // y坐标
} Position;

typedef struct {
    Position *base;        // 栈底指针
    Position *top;         // 栈顶指针
    int stack_size;        // 当前分配的栈可使用的最大存储量
} SqStack;

int mazeSize;
Position directions[4] = {{1, 0}, {0, 1}, {-1, 0}, {0, -1}}; // 右、下、左、上

// 初始化栈
int InitStack(SqStack *s) {
    s->base = (Position *)malloc(STACK_INIT_SIZE * sizeof(Position));
    if (!s->base) return -1;  // 开辟内存失败
    s->top = s->base;    // 将栈顶指针top初始化为栈底指针base，表示栈目前为空
    s->stack_size = STACK_INIT_SIZE;
    return 0;
}

// 入栈
int Push(SqStack *s, Position pos) {
    if (s->top - s->base == s->stack_size) { // 如果栈满，增加空间
        Position *new_base = (Position *)realloc(s->base, (s->stack_size + STACK_INCREMENT) * sizeof(Position));
        if (!new_base) return -1; // 内存分配失败
        s->base = new_base;
        s->top = s->base + s->stack_size;
        s->stack_size += STACK_INCREMENT;
    }
    *s->top++ = pos; // 入栈
    return 0;
}

// 出栈
int Pop(SqStack *s, Position *pos) {
    if (s->top == s->base) return -1;  // 栈空
    *pos = *--s->top; // 出栈
    return 0;
}


int dfs(int maze[mazeSize][mazeSize], Position start, Position end) {
    SqStack stack;
    if (InitStack(&stack) != 0) return -1; // 初始化栈失败

    int vis[mazeSize][mazeSize];
    for (int i = 1; i <= mazeSize; i++)
        for (int j = 1; j <= mazeSize; j++)
            vis[i][j] == 0;

    Push(&stack, start); // 从起点入栈
    vis[start.x][start.y] = 1; // 标记起点为已访问

    Position current;  // 指针

    while (stack.top != stack.base) {
        Pop(&stack, &current);
        printf("Visited: (%d, %d)\n", current.x, current.y); // 打印当前访问位置

        // 检查是否到达终点
        if (current.x == end.x && current.y == end.y) {
            printf("Reached the endpoint (%d, %d)\n", end.x, end.y);
            free(stack.base);
            return 1; // 找到路径
        }


        for (int i = 0; i < 4; i++) {
            int d_x = current.x + directions[i].x;
            int d_y = current.y + directions[i].y;

            if (d_x < mazeSize && d_x > 0 && d_y < mazeSize && d_y > 0 && maze[d_x][d_y] == 1 && vis[d_x][d_y] == 0) {
                vis[d_x][d_y] = 1;
                Position next_step = {d_x, d_y};
                Push(&stack, next_step);
            }
        }

        printf("No path found from start to end.\n");
        free(stack.base);
        return 0; // 没有找到路径
    }
}



int main(void){
    scanf("%d", &mazeSize);

    int maze[mazeSize][mazeSize];
    for(int i = 1; i <= mazeSize; i++){
        for(int j = 1; j <= mazeSize; j++){
            scanf("%d", &maze[i][j]);
        }
    }

    Position start = {0, 0};
    Position end = {mazeSize - 1, mazeSize - 1};

    dfs(maze, start, end);
    return 0;
}
