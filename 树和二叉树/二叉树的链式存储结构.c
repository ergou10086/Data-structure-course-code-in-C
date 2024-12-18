#include <stdio.h>
#include <stdlib.h>

#define MAX_TREE_SIZE 100   // 二叉树的最大节点数
#define STACKINITSIZE 20
#define INCREASEMENT 10

// 二叉树链式存储节点结构体定义
typedef struct BiTNode {
    int data;
    struct BiTNode *lchild, *rchild;  // 左右孩子指针
} BiTNode, *BiTree;

// 栈结构体
typedef struct SqStack
{
    BiTNode *base;   //栈底指针
    BiTNode *top;   //栈顶指针
    int stacksize;   //顺序栈空间大小
}SqStack;  //定义顺序栈结构


int value[MAX_TREE_SIZE];
int n, cnt = 0;


// 栈的各种操作
// 初始化栈
void InitStack(SqStack *S) {
    S->base = (BiTNode *)malloc(STACKINITSIZE * sizeof(BiTNode));
    if (!S->base) {
        printf("内存分配失败！\n");
        exit(1);
    }
    S->top = S->base;
    S->stacksize = STACKINITSIZE;
}

// 判断栈是否为空
int StackEmpty(SqStack S) {
    return S.top == S.base;
}

// 入栈操作
void Push(SqStack *S, BiTNode *e) {
    if (S->top - S->base >= S->stacksize) {
        // 栈空间不足，扩容
        S->base = (BiTNode *)realloc(S->base, (S->stacksize + INCREASEMENT) * sizeof(BiTNode));
        if (!S->base) {
            printf("内存分配失败！\n");
            exit(1);
        }
        S->top = S->base + S->stacksize;
        S->stacksize += INCREASEMENT;
    }
    *(S->top++) = *e;
}

// 出栈操作
void Pop(SqStack *S) {
    if (StackEmpty(*S)) {
        printf("栈为空，无法出栈！\n");
        return;
    }
    --S->top;
}


// 创建二叉树，先序序列创建二叉链表
void createBiTree(BiTree *T) {
    int val = value[cnt];
    if (val == -1) {
        *T = NULL;
    } else {
        *T = (BiTNode *)malloc(sizeof(BiTNode));
        (*T)->data = val;
        cnt++;  // 处理完当前节点，索引后移一位，准备处理左子树
        createBiTree(&((*T)->lchild));
        createBiTree(&((*T)->rchild));
    }
}

// 递归先序遍历
void preOrder(BiTree tree) {
    if (tree) {
        // 先遍历根节点，然后左节点，右节点
        if (tree->data!= 0) {
            printf("%d ", tree->data);
            preOrder(tree->lchild);
            preOrder(tree->rchild);
        }
    }
}

// 前序遍历（非递归），使用自定义栈结构体
void preOrderNonRecursive(BiTree tree) {
    if (tree == NULL) return;

    SqStack S;
    InitStack(&S);

    BiTNode *curr = tree;

    while (curr || !StackEmpty(S)) {
        if (curr){
            if(curr->data){
                printf("%d ", curr->data);
            }
            Push(&S, curr);
            curr = curr->lchild;
        }
        else{
            curr = S.top;
            Pop(&S);
            curr = curr->rchild;
        }
    }
}

// 递归中序遍历
void inOrder(BiTree T) {
    if (T) {
        // 先遍历左节点，然后根节点，右节点
        if (T->data!= 0) {
            inOrder(T->lchild);
            printf("%d ", T->data);
            inOrder(T->rchild);
        }
    }
}

// 中序遍历（非递归），使用自定义栈结构体
void inOrderNonRecursive(BiTree* tree) {
    if (tree == NULL) return;

    SqStack S;
    InitStack(&S);

    BiTNode *curr = tree;

    while (curr || !StackEmpty(S)) {
        if(curr){
            Push(&S, curr);
            curr = curr -> lchild;
        }else{
            curr = S.top;
            Pop(&S);
            if(curr->data){
                printf("%d ", curr->data);
            }
            curr = curr -> rchild;
        }
    }
}


// 递归后序遍历
void postOrder(BiTree T) {
    if (T) {
        if(T->data != 0) {
            postOrder(T->lchild);
            postOrder(T->rchild);
            printf("%d ", T->data);
        }
    }
}

// 后序遍历（非递归）
void postOrderNonRecursive(BiTree t) {

}

/*
// 层序遍历
void levelOrder(BiTree tree) {
    if (tree == NULL) return;

    BiTree *queue[MAX_TREE_SIZE];
    int front = 0, rear = 0;

    queue[rear++] = tree;  // 将根节点入队

    while (front < rear) {
        BiTNode *node = queue[front++];
        if(node->data != 0) {
            printf("%d ", node->data);
            if (node->lchild) {
                queue[rear++] = node->lchild;
            }
            if (node->rchild) {
                queue[rear++] = node->rchild;
            }
        }
    }
}
*/

// 修改节点值
BiTNode* modifyNode(BiTree T, int oldValue, int newValue) {
    if (T == NULL) return NULL;

    if (T->data == oldValue) {
        T->data = newValue;
    }
    modifyNode(T->lchild, oldValue, newValue);
    modifyNode(T->rchild, oldValue, newValue);

    return T;
}

// 计算二叉树的节点个数
int countNodes(BiTree T) {
    if (T == NULL) {
        return 0;
    } else {
        return 1 + countNodes(T->lchild) + countNodes(T->rchild);
    }
}

// 计算二叉树的高度
int treeHeight(BiTree T) {
    if (T == NULL) {
        return 0;
    } else {
        int leftHeight = treeHeight(T->lchild);
        int rightHeight = treeHeight(T->rchild);
        return 1 + (leftHeight > rightHeight? leftHeight : rightHeight);
    }
}

// 查找指定值的节点
BiTNode* findNode(BiTree T, int valueToFind) {
    if (T == NULL) {
        return NULL;
    }
    if (T->data == valueToFind) {
        return T;
    }
    BiTNode *leftResult = findNode(T->lchild, valueToFind);
    if (leftResult!= NULL) {
        return leftResult;
    }
    return findNode(T->rchild, valueToFind);
}

int main() {
    BiTree T = NULL;
    scanf("%d", &n);
    for (int i = 0; i < n; i++) {
        scanf("%d", &value[i]);
    }

    createBiTree(&T);

    printf("先序遍历（递归）: ");
    preOrder(T);
    printf("\n");

    printf("先序遍历（非递归）: ");
    preOrderNonRecursive(T);
    printf("\n");

    printf("中序遍历（递归）: ");
    inOrder(T);
    printf("\n");

    printf("中序遍历（非递归）: ");
    inOrderNonRecursive(T);
    printf("\n");

    printf("后序遍历（递归）: ");
    postOrder(T);
    printf("\n");

    printf("后序遍历（非递归）: ");
    postOrderNonRecursive(T);
    printf("\n");

    /*
    printf("层序遍历: ");
    levelOrder(T);
    printf("\n");
    */

    int oldValue, newValue;
    printf("输入要修改的节点值和新值 (旧值 新值): ");
    scanf("%d %d", &oldValue, &newValue);
    modifyNode(T, oldValue, newValue);

    printf("修改后的先序遍历: ");
    preOrder(T);
    printf("\n");

    // 计算并输出节点个数
    int nodeCount = countNodes(T);
    printf("二叉树的节点个数: %d\n", nodeCount);

    // 计算并输出树的高度
    int treeHeightValue = treeHeight(T);
    printf("二叉树的高度: %d\n", treeHeightValue);

    // 查找指定值的节点并输出结果
    int valueToFind;
    printf("输入要查找的节点值: ");
    scanf("%d", &valueToFind);
    BiTNode *foundNode = findNode(T, valueToFind);
    if (foundNode!= NULL) {
        printf("找到值为 %d 的节点，地址为: %p\n", valueToFind, foundNode);
    } else {
        printf("未找到值为 %d 的节点\n", valueToFind);
    }

    return 0;
}

/*
6
5 3 8 6 2 1
 */