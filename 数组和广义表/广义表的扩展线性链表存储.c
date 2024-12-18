#include <stdio.h>
#include <stdlib.h>

typedef struct GLNode {
    int tag;// ��־����������Ԫ�ؽ��ͱ���

    union {  // Ԫ�ؽ��ͱ�������ϲ���
        char atom;//ԭ�ӽ���ֵ��
        struct GLNode* hp;//����ı�ͷָ��
    }un;
    struct GLNode* tp;//�����tp�൱�������nextָ�룬����ָ����һ������Ԫ��
}GLNode, * GList;


// ����ԭ�ӽ��
GList CreateAtomNode(char data) {
    GList newNode = (GList)malloc(sizeof(GLNode));
    if (newNode == NULL) {
        printf("�ڴ����ʧ�ܣ�\n");
        exit(1);
    }
    newNode->tag = 0;
    newNode->un.atom = data;
    newNode->tp = NULL;
    return newNode;
}

// ��������
GList CreateListNode(GList head, GList tail) {
    GList newNode = (GList)malloc(sizeof(GLNode));
    if (newNode == NULL) {
        printf("�ڴ����ʧ�ܣ�\n");
        exit(1);
    }
    newNode->tag = 1;
    newNode->un.hp = head;
    newNode->tp = tail;
    return newNode;
}

// �����ַ�����ʾ����������򵥵ĵݹ����ʵ��ʾ���������Ƹ��ิ���������
GList CreateGList(char* str) {
    GList newNode;
    if (*str == '\0') {
        return NULL;
    }
    if (*str == '(') {
        str++;
        newNode = (GList)malloc(sizeof(GLNode));
        if (newNode == NULL) {
            printf("�ڴ����ʧ�ܣ�\n");
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

// �������ȣ��ݹ�ͳ�ƣ�
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

// ��������ȣ��ݹ���㣩
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

// ����������ʽ�������
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

// �ͷŹ�����ڴ�
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
    printf("������ȣ�%d\n", GListLength(gl));
    printf("�������ȣ�%d\n", GListDepth(gl));
    printf("����������");
    PrintGList(gl);
    printf("\n");
    FreeGList(gl);
    return 0;
}