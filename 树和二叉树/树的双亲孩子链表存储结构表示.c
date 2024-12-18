#include <stdio.h>
#include <stdlib.h>

#define MAX_TREE 110

typedef int TreeElemType;

// ���ӽڵ�ṹ��,���ӽ��ָ��
typedef struct CTNode{
    int child;
    struct CTNode* next;
}CTNode, *ChildPtr;

// ��˫�׵ĺ�������Ľ��ṹ�弰��ָ��
typedef struct CPNode{
    int parent;    // ˫�׽ڵ�λ��
    TreeElemType data;
    ChildPtr headChild;     // ��������ͷָ��
}CPNode;

// ��˫�׵ĺ�����������Ľṹ��
typedef struct CTTree{
    CPNode nodes[MAX_TREE];
    int root;   // ��λ��
    int n;   // ���Ľڵ���
}CTTree;


// ��ʼ����
void InitTree(int arr[], CTTree* tree){
    int i;
    // ���������arr��-1��Ϊ������־
    tree->n = 0;
    for (i = 0; arr[i]!= -1; i++) {
        // ��ʼ��ÿ���ڵ��˫����Ϊ-1����������ͷָ��ΪNULL
        tree->nodes[i].parent = -1;
        tree->nodes[i].data = arr[i];
        tree->nodes[i].headChild = NULL;
        tree->n++;
    }
    tree->root = 0;
}


// ��Ӻ��ӽڵ����
void AddChild(int parentIndex, int childIndex, CTTree* tree){
    CTNode* newChild = (CTNode*)malloc(sizeof(CTNode));
    newChild->child = childIndex;
    // ���뵽��Ӧ˫�׽ڵ�ĺ�������ͷ��
    newChild->next = tree->nodes[parentIndex].headChild;
    // ��������
    tree->nodes[parentIndex].headChild = newChild;
    tree->nodes[childIndex].parent = parentIndex;
}


// ���Ķ���ָ���нڵ������ӽڵ���
int TreeDegree(CTTree* tree) {
    int maxDegree = 0;
    int i;
    // �������е�ÿ���ڵ�
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
    printf("���Ķ�Ϊ: %d\n", TreeDegree(&tree));
    return 0;
}