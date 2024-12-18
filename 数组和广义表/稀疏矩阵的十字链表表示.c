#include <stdio.h>
#include <stdlib.h>

#define MAXSIZE 12500
#define MAXRC 100
const int ERROR = -1;
const int OVERFLOW = 1;
const int OK = 0;

typedef struct OLNode {
    int i, j;                    // 该非零元的行和列下标
    int ele;                     // 非零元的值
    struct OLNode *right, *down; // 行链表和列链表的后继指针
} OLNode, *OLink;

typedef struct {
    OLink *rhead, *chead;  // 行链表头指针数组，列链表头指针数组
    int mu, nu, tu;        // 稀疏矩阵的行数，列数，非零元个数
} CrossList;

// 创建一个新的OLNode节点
OLink CreateNode(int i, int j, int ele) {
    OLink newNode = (OLink)malloc(sizeof(OLNode));
    if (!newNode) {
        printf("Memory allocation failed.\n");
        return NULL;
    }
    newNode->i = i;
    newNode->j = j;
    newNode->ele = ele;
    newNode->right = newNode->down = NULL;
    return newNode;
}

// 初始化稀疏矩阵
int InitCrossList(CrossList *M, int mu, int nu, int tu) {
    M->mu = mu;
    M->nu = nu;
    M->tu = tu;

    // 为行链表和列链表分配内存
    M->rhead = (OLink *)malloc((mu + 1) * sizeof(OLink));
    M->chead = (OLink *)malloc((nu + 1) * sizeof(OLink));
    if (!M->rhead || !M->chead) {
        printf("Memory allocation failed.\n");
        return OVERFLOW;
    }

    // 初始化每一行和每一列的头指针为空
    for (int i = 1; i <= mu; i++) {
        M->rhead[i] = NULL;
    }
    for (int j = 1; j <= nu; j++) {
        M->chead[j] = NULL;
    }

    return OK;
}

// 插入一个非零元素
int InsertElement(CrossList *M, int i, int j, int ele) {
    if (i < 1 || i > M->mu || j < 1 || j > M->nu) {
        printf("Index out of bounds.\n");
        return ERROR;
    }

    OLink newNode = CreateNode(i, j, ele);
    if (!newNode) return ERROR;

    // 插入到行链表中
    OLink p = M->rhead[i];
    if (!p || p->j > j) {
        newNode->right = p;
        M->rhead[i] = newNode;
    } else {
        while (p->right && p->right->j < j) {
            p = p->right;
        }
        newNode->right = p->right;
        p->right = newNode;
    }

    // 插入到列链表中
    p = M->chead[j];
    if (!p || p->i > i) {
        newNode->down = p;
        M->chead[j] = newNode;
    } else {
        while (p->down && p->down->i < i) {
            p = p->down;
        }
        newNode->down = p->down;
        p->down = newNode;
    }

    return OK;
}

// 打印稀疏矩阵
void PrintCrossList(CrossList *M) {
    for (int i = 1; i <= M->mu; i++) {
        OLink p = M->rhead[i];
        for (int j = 1; j <= M->nu; j++) {
            if (p && p->j == j) {
                printf("%d ", p->ele);
                p = p->right;
            } else {
                printf("0 ");
            }
        }
        printf("\n");
    }
}

// 释放稀疏矩阵
void FreeCrossList(CrossList *M) {
    for (int i = 1; i <= M->mu; i++) {
        OLink p = M->rhead[i];
        while (p) {
            OLink temp = p;
            p = p->right;
            free(temp);
        }
    }

    free(M->rhead);
    free(M->chead);
}

int main() {
    CrossList M;
    int mu = 5, nu = 5, tu = 5;

    // 初始化一个5x5的稀疏矩阵，非零元有5个
    if (InitCrossList(&M, mu, nu, tu) != OK) {
        printf("Matrix initialization failed.\n");
        return -1;
    }

    // 插入非零元素
    InsertElement(&M, 1, 1, 5);
    InsertElement(&M, 1, 4, 8);
    InsertElement(&M, 2, 2, 7);
    InsertElement(&M, 4, 4, 3);
    InsertElement(&M, 5, 5, 2);

    // 打印稀疏矩阵
    printf("Sparse matrix in CrossList format:\n");
    PrintCrossList(&M);

    // 释放稀疏矩阵的内存
    FreeCrossList(&M);

    return 0;
}
