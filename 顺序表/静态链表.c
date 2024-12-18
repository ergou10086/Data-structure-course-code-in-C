#include <stdio.h>
#include <stdlib.h>

#define INITIAL_SIZE 10
#define LISTINCREMENT 5
#define OK 1
#define ERROR 0
#define OVERFLOW -1

const int MAX_SIZE = 15;

typedef struct SNode {
    int data;   // ����
    int cur;    // �α꣬����next�ڵڼ���λ��
}ListNode;
typedef ListNode SLinkList[MAX_SIZE];
// ListNode�ǽṹ�����͵ı���������һ������ڵ�
// SLinkList[1000] ��һ������ 15 �� component �ṹ��Ԫ�ص�����


// ����һ����������
void InitList(SLinkList s){
    for(int i = 1; i < MAX_SIZE - 1; i++) {
        // ÿ���ڵ�� next ָ����һ���ڵ�
        s[i].cur = i + 1;
    }
    s[MAX_SIZE - 1].cur = 0;   // �����������һ��Ԫ����Ϊ�գ���ʾ�������
    //��ʼ��ʱΪ�յľ�̬���������ݽ�㣬ͷ�����α�Ϊ-1
    s[0].cur = -1;
}


// ����һ�����нڵ�
int MallocList(SLinkList s){
    int i = s[0].cur;  // ��ǰ�����һ��Ԫ�ص�cur���ֵ����Ҫ���صĵ�һ�����ÿռ���±�
    // ����������л��п��ÿռ���ô�ͽ��з��䣨���ı�����ͷָ���ָ��
    if(s[1].cur)
        s[1].cur = s[i].cur; // ����һ����������������
    return i;
}


// �ͷŻؾ�̬��������������
// �����뵽���������һ�����ǰ
void FreeList(SLinkList s, int k) {
    // �Ȱ�Ҫ�ͷŵĵ�k���ڵ�ָ�򱣴浽��һ�����нڵ��cur
    s[k].cur = s[0].cur;
    // ���ô����һ�����нڵ�ָ��k
    s[0].cur = k;
}


// ��ѯ������
int ListLength(SLinkList s){
    int i, j=0;
    i = s[MAX_SIZE-1].cur;   //iָ���һ�����

    while (i){    //���һ������ָ����Ϊ�գ�����ѭ��
        ++j;
        i = s[i].cur;
    }
    return j;
}


// �������ݵ�����ͷ�巨
int ListInsertHead(SLinkList s, int value) {

    int i = MallocList(s);//����ռ�
    if(i == 0)//���Ϊ���ʾ����ռ�ʧ��
    {
        printf("����ڵ�ռ�ʧ��.\n");
        return ERROR;
    }

    s[i].data = value;
    //���֮ǰ��̬�����������ݽ�㣬��Ҫ����ͷ����ָ��
    if(s[0].cur == -1)
    {
        s[i].cur = -1;
        //space[0].cur = i;
    }
    else //���֮ǰ�Ѿ������ݽ����ôֱ��ͷ��
    {
        s[i].cur = s[0].cur;
    }
    s[0].cur = i;
    return OK;
}



// ɾ�������е�i��λ�õ�Ԫ�أ���1��ʼ��
int ListDelete(SLinkList s, int i, int *e) {
    // ���λ���Ƿ�Ϸ�
    if (i < 1 || i > ListLength(s)) return ERROR;

}



//����Ԫ��ʵ��


// ��ӡ��̬����
void DisplayList(SLinkList s) {
    int i = s[0].cur;//�ӵ�һ�����ݽ�㿪ʼ����
    while (i != -1)//�����е����ݽ���ӡ
    {
        printf("%d-->", s[i].data);
        i = s[i].cur; // p = p->next;
    }
    printf("Nul.\n");
}






int main() {
    SLinkList s;

    // ��ʼ������
    InitList(s);

    // ����Ԫ��
    ListInsertHead(s, 10);
    ListInsertHead(s, 21);
    ListInsertHead(s, 13);
    ListInsertHead(s, 16);
    ListInsertHead(s, 11);
    DisplayList(s);

    // ɾ��Ԫ��
    int rec = 0;
    ListDelete(s,3, &rec);
    printf("%d\n", rec);
    DisplayList(s);

    return 0;
}
