#include <stdio.h>
#include <stdlib.h>

#define MAX_TREE_SIZE 100   // 二叉树的最大节点数

typedef int SqBiTree[MAX_TREE_SIZE];

// 初始化树
void InitBiTree(SqBiTree tree) {
    for (int i = 0; i < MAX_TREE_SIZE; i++) {
        tree[i] = 0; // 0 表示该位置为空
    }
}

// 插入节点
void InsertBiTree(SqBiTree tree, int index, int value) {
    if (index < MAX_TREE_SIZE) {
        tree[index] = value; // 插入值
    } else {
        printf("Index out of bounds!\n");
    }
}


// 从前序序列构造二叉树
void CreateBiTree(SqBiTree tree, int* preorder, int* index, int n) {
    if (*index >= n || preorder[*index] == 0) {
        (*index)++;
        return;
    }

    tree[0] = preorder[*index]; // 根节点
    int currentIndex = 0;
    (*index)++;

    // 递归构造左子树
    CreateBiTree(tree + 1, preorder, index, n);
    // 递归构造右子树
    CreateBiTree(tree + 2, preorder, index, n);
}


// 层序遍历
void LevelOrder(SqBiTree tree) {
    for (int i = 0; i < MAX_TREE_SIZE; i++) {
        if (tree[i] != 0) {
            printf("%d ", tree[i]);
        }
    }
}


// 前序遍历
void PreOrder(SqBiTree tree, int index) {
    if (index < MAX_TREE_SIZE && tree[index] != 0) {
        printf("%d ", tree[index]); // 访问当前节点
        PreOrder(tree, 2 * index + 1); // 访问左子树
        PreOrder(tree, 2 * index + 2); // 访问右子树
    }
}


// 中序遍历
void InOrder(SqBiTree tree, int index) {
    if (index < MAX_TREE_SIZE && tree[index] != 0) {
        InOrder(tree, 2 * index + 1); // 访问左子树
        printf("%d ", tree[index]); // 访问当前节点
        InOrder(tree, 2 * index + 2); // 访问右子树
    }
}


// 后序遍历
void PostOrder(SqBiTree tree, int index) {
    if (index < MAX_TREE_SIZE && tree[index] != 0) {
        PostOrder(tree, 2 * index + 1); // 访问左子树
        PostOrder(tree, 2 * index + 2); // 访问右子树
        printf("%d ", tree[index]); // 访问当前节点
    }
}


int main() {
    SqBiTree tree;
    InitBiTree(tree); // 初始化二叉树

    // 插入节点
    InsertBiTree(tree, 0, 1); // 根节点
    InsertBiTree(tree, 1, 2); // 左子节点
    InsertBiTree(tree, 2, 3); // 右子节点
    InsertBiTree(tree, 3, 4); // 左子节点的左子节点
    InsertBiTree(tree, 4, 5); // 左子节点的右子节点

    // 遍历
    printf("Pre-order Traversal: ");
    PreOrder(tree, 0);
    printf("\n");

    printf("In-order Traversal: ");
    InOrder(tree, 0);
    printf("\n");

    printf("Post-order Traversal: ");
    PostOrder(tree, 0);
    printf("\n");

    return 0;
}
