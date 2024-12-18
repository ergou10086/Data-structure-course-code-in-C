#include <stdio.h>
#include <stdlib.h>

typedef struct GLNode {
    int tag;// 标志域，用于区分元素结点和表结点

    union {  // 元素结点和表结点的联合部分
        char atom;//原子结点的值域
        struct GLNode* hp;//表结点的表头指针
    }un;
    struct GLNode* tp;//这里的tp相当于链表的next指针，用于指向下一个数据元素
}GLNode, * GList;


// 创建原子结点
GList CreateAtomNode(char data) {
    GList newNode = (GList)malloc(sizeof(GLNode));
    if (newNode == NULL) {
        printf("内存分配失败！\n");
        exit(1);
    }
    newNode->tag = 0;
    newNode->un.atom = data;
    newNode->tp = NULL;
    return newNode;
}

// 创建表结点
GList CreateListNode(GList head, GList tail) {
    GList newNode = (GList)malloc(sizeof(GLNode));
    if (newNode == NULL) {
        printf("内存分配失败！\n");
        exit(1);
    }
    newNode->tag = 1;
    newNode->un.hp = head;
    newNode->tp = tail;
    return newNode;
}

// 根据字符串表示创建广义表（简单的递归解析实现示例，可完善更多复杂情况处理）
GList CreateGList(char* str) {
    GList newNode;
    if (*str == '\0') {
        return NULL;
    }
    if (*str == '(') {
        str++;
        newNode = (GList)malloc(sizeof(GLNode));
        if (newNode == NULL) {
            printf("内存分配失败！\n");
            exit(1);
        }
        newNode->tag = 1;
        newNode->un.hp = CreateGList(str);
        while (*str!= '\0' && *str!= ')') {
            str++;
            newNode->tp = CreateGList(str);
        }
        if (*str == ')') {
            str++;
        }
        return newNode;
    } else {
        newNode = CreateAtomNode(*str);
        str++;
        return newNode;
    }
}

// 求广义表长度（递归统计）
int GListLength(GList gl) {
    int length = 0;
    GList p = gl;
    if (gl == NULL) {
        return 0;
    }
    if (gl->tag == 1) {
        p = gl->un.hp;
    }
    while (p!= NULL) {
        length++;
        p = p->tp;
    }
    return length;
}

// 求广义表深度（递归计算）
int GListDepth(GList gl) {
    int maxDepth = 0;
    int dep;
    GList p;
    if (gl == NULL) {
        return 1;
    }
    if (gl->tag == 0) {
        return 0;
    }
    p = gl->un.hp;
    while (p!= NULL) {
        dep = GListDepth(p);
        if (dep > maxDepth) {
            maxDepth = dep;
        }
        p = p->tp;
    }
    return maxDepth + 1;
}

// 输出广义表（格式化输出）
void PrintGList(GList gl) {
    if (gl == NULL) {
        printf("()");
        return;
    }
    if (gl->tag == 0) {
        printf("%c", gl->un.atom);
    } else {
        printf("(");
        PrintGList(gl->un.hp);
        GList p = gl->tp;
        while (p!= NULL) {
            printf(",");
            PrintGList(p);
            p = p->tp;
        }
        printf(")");
    }
}

// 释放广义表内存
void FreeGList(GList gl) {
    if (gl == NULL) {
        return;
    }
    if (gl->tag == 0) {
        free(gl);
    } else {
        FreeGList(gl->un.hp);
        FreeGList(gl->tp);
        free(gl);
    }
}


int main() {
    char str[] = "(a,(b,c))";
    GList gl = CreateGList(str);
    printf("广义表长度：%d\n", GListLength(gl));
    printf("广义表深度：%d\n", GListDepth(gl));
    printf("广义表输出：");
    PrintGList(gl);
    printf("\n");
    FreeGList(gl);
    return 0;
}