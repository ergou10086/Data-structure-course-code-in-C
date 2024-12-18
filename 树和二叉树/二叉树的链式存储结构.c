#include <stdio.h>
#include <stdlib.h>

#define MAX_TREE_SIZE 100   // �����������ڵ���
#define STACKINITSIZE 20
#define INCREASEMENT 10

// ��������ʽ�洢�ڵ�ṹ�嶨��
typedef struct BiTNode {
    int data;
    struct BiTNode *lchild, *rchild;  // ���Һ���ָ��
} BiTNode, *BiTree;

// ջ�ṹ��
typedef struct SqStack
{
    BiTNode *base;   //ջ��ָ��
    BiTNode *top;   //ջ��ָ��
    int stacksize;   //˳��ջ�ռ��С
}SqStack;  //����˳��ջ�ṹ


int value[MAX_TREE_SIZE];
int n, cnt = 0;


// ջ�ĸ��ֲ���
// ��ʼ��ջ
void InitStack(SqStack *S) {
    S->base = (BiTNode *)malloc(STACKINITSIZE * sizeof(BiTNode));
    if (!S->base) {
        printf("�ڴ����ʧ�ܣ�\n");
        exit(1);
    }
    S->top = S->base;
    S->stacksize = STACKINITSIZE;
}

// �ж�ջ�Ƿ�Ϊ��
int StackEmpty(SqStack S) {
    return S.top == S.base;
}

// ��ջ����
void Push(SqStack *S, BiTNode *e) {
    if (S->top - S->base >= S->stacksize) {
        // ջ�ռ䲻�㣬����
        S->base = (BiTNode *)realloc(S->base, (S->stacksize + INCREASEMENT) * sizeof(BiTNode));
        if (!S->base) {
            printf("�ڴ����ʧ�ܣ�\n");
            exit(1);
        }
        S->top = S->base + S->stacksize;
        S->stacksize += INCREASEMENT;
    }
    *(S->top++) = *e;
}

// ��ջ����
void Pop(SqStack *S) {
    if (StackEmpty(*S)) {
        printf("ջΪ�գ��޷���ջ��\n");
        return;
    }
    --S->top;
}


// �������������������д�����������
void createBiTree(BiTree *T) {
    int val = value[cnt];
    if (val == -1) {
        *T = NULL;
    } else {
        *T = (BiTNode *)malloc(sizeof(BiTNode));
        (*T)->data = val;
        cnt++;  // �����굱ǰ�ڵ㣬��������һλ��׼������������
        createBiTree(&((*T)->lchild));
        createBiTree(&((*T)->rchild));
    }
}

// �ݹ��������
void preOrder(BiTree tree) {
    if (tree) {
        // �ȱ������ڵ㣬Ȼ����ڵ㣬�ҽڵ�
        if (tree->data!= 0) {
            printf("%d ", tree->data);
            preOrder(tree->lchild);
            preOrder(tree->rchild);
        }
    }
}

// ǰ��������ǵݹ飩��ʹ���Զ���ջ�ṹ��
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

// �ݹ��������
void inOrder(BiTree T) {
    if (T) {
        // �ȱ�����ڵ㣬Ȼ����ڵ㣬�ҽڵ�
        if (T->data!= 0) {
            inOrder(T->lchild);
            printf("%d ", T->data);
            inOrder(T->rchild);
        }
    }
}

// ����������ǵݹ飩��ʹ���Զ���ջ�ṹ��
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


// �ݹ�������
void postOrder(BiTree T) {
    if (T) {
        if(T->data != 0) {
            postOrder(T->lchild);
            postOrder(T->rchild);
            printf("%d ", T->data);
        }
    }
}

// ����������ǵݹ飩
void postOrderNonRecursive(BiTree t) {

}

/*
// �������
void levelOrder(BiTree tree) {
    if (tree == NULL) return;

    BiTree *queue[MAX_TREE_SIZE];
    int front = 0, rear = 0;

    queue[rear++] = tree;  // �����ڵ����

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

// �޸Ľڵ�ֵ
BiTNode* modifyNode(BiTree T, int oldValue, int newValue) {
    if (T == NULL) return NULL;

    if (T->data == oldValue) {
        T->data = newValue;
    }
    modifyNode(T->lchild, oldValue, newValue);
    modifyNode(T->rchild, oldValue, newValue);

    return T;
}

// ����������Ľڵ����
int countNodes(BiTree T) {
    if (T == NULL) {
        return 0;
    } else {
        return 1 + countNodes(T->lchild) + countNodes(T->rchild);
    }
}

// ����������ĸ߶�
int treeHeight(BiTree T) {
    if (T == NULL) {
        return 0;
    } else {
        int leftHeight = treeHeight(T->lchild);
        int rightHeight = treeHeight(T->rchild);
        return 1 + (leftHeight > rightHeight? leftHeight : rightHeight);
    }
}

// ����ָ��ֵ�Ľڵ�
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

    printf("����������ݹ飩: ");
    preOrder(T);
    printf("\n");

    printf("����������ǵݹ飩: ");
    preOrderNonRecursive(T);
    printf("\n");

    printf("����������ݹ飩: ");
    inOrder(T);
    printf("\n");

    printf("����������ǵݹ飩: ");
    inOrderNonRecursive(T);
    printf("\n");

    printf("����������ݹ飩: ");
    postOrder(T);
    printf("\n");

    printf("����������ǵݹ飩: ");
    postOrderNonRecursive(T);
    printf("\n");

    /*
    printf("�������: ");
    levelOrder(T);
    printf("\n");
    */

    int oldValue, newValue;
    printf("����Ҫ�޸ĵĽڵ�ֵ����ֵ (��ֵ ��ֵ): ");
    scanf("%d %d", &oldValue, &newValue);
    modifyNode(T, oldValue, newValue);

    printf("�޸ĺ���������: ");
    preOrder(T);
    printf("\n");

    // ���㲢����ڵ����
    int nodeCount = countNodes(T);
    printf("�������Ľڵ����: %d\n", nodeCount);

    // ���㲢������ĸ߶�
    int treeHeightValue = treeHeight(T);
    printf("�������ĸ߶�: %d\n", treeHeightValue);

    // ����ָ��ֵ�Ľڵ㲢������
    int valueToFind;
    printf("����Ҫ���ҵĽڵ�ֵ: ");
    scanf("%d", &valueToFind);
    BiTNode *foundNode = findNode(T, valueToFind);
    if (foundNode!= NULL) {
        printf("�ҵ�ֵΪ %d �Ľڵ㣬��ַΪ: %p\n", valueToFind, foundNode);
    } else {
        printf("δ�ҵ�ֵΪ %d �Ľڵ�\n", valueToFind);
    }

    return 0;
}

/*
6
5 3 8 6 2 1
 */