#include <stdio.h>
#include <stdlib.h>

#define MAX_TREE 110

typedef int TreeElemType;

// 孩子节点结构体,孩子结点指针
typedef struct CTNode{
    int child;
    struct CTNode* next;
}CTNode, *ChildPtr;

// 带双亲的孩子链表的结点结构体及其指针
typedef struct CPNode{
    int parent;    // 双亲节点位置
    TreeElemType data;
    ChildPtr headChild;     // 孩子链表头指针
}CPNode;

// 带双亲的孩子链表的树的结构体
typedef struct CTTree{
    CPNode nodes[MAX_TREE];
    int root;   // 根位置
    int n;   // 树的节点数
}CTTree;


// 初始化树
void InitTree(int arr[], CTTree* tree){
    int i;
    // 输入的数组arr以-1作为结束标志
    tree->n = 0;
    for (i = 0; arr[i]!= -1; i++) {
        // 初始化每个节点的双亲设为-1，孩子链表头指针为NULL
        tree->nodes[i].parent = -1;
        tree->nodes[i].data = arr[i];
        tree->nodes[i].headChild = NULL;
        tree->n++;
    }
    tree->root = 0;
}


// 添加孩子节点操作
void AddChild(int parentIndex, int childIndex, CTTree* tree){
    CTNode* newChild = (CTNode*)malloc(sizeof(CTNode));
    newChild->child = childIndex;
    // 插入到对应双亲节点的孩子链表头部
    newChild->next = tree->nodes[parentIndex].headChild;
    // 更新索引
    tree->nodes[parentIndex].headChild = newChild;
    tree->nodes[childIndex].parent = parentIndex;
}


// 树的度是指树中节点的最大子节点数
int TreeDegree(CTTree* tree) {
    int maxDegree = 0;
    int i;
    // 遍历树中的每个节点
    for (i = 0; i < tree->n; i++) {
        int degree = 0;
        CTNode* p = tree->nodes[i].headChild;
        while (p!= NULL) {
            degree++;
            p = p->next;
        }
        if (degree > maxDegree) {
            maxDegree = degree;
        }
    }
    return maxDegree;
}


int main() {
    int arr[] = {1, 2, 3, -1};
    CTTree tree;
    InitTree(arr, &tree);
    AddChild(0, 1, &tree);
    AddChild(0, 2, &tree);
    printf("树的度为: %d\n", TreeDegree(&tree));
    return 0;
}