#include <stdio.h>
#include <stdlib.h>

#define INITIAL_SIZE 10
#define LISTINCREMENT 5
#define OK 1
#define ERROR 0
#define OVERFLOW -1

const int MAX_SIZE = 15;

typedef struct SNode {
    int data;   // 数据
    int cur;    // 游标，代表next在第几号位置
}ListNode;
typedef ListNode SLinkList[MAX_SIZE];
// ListNode是结构体类型的别名，代表一个链表节点
// SLinkList[1000] 是一个包含 15 个 component 结构体元素的数组


// 创建一个空闲链表
void InitList(SLinkList s){
    for(int i = 1; i < MAX_SIZE - 1; i++) {
        // 每个节点的 next 指向下一个节点
        s[i].cur = i + 1;
    }
    s[MAX_SIZE - 1].cur = 0;   // 备用链表最后一个元素置为空，表示链表结束
    //初始化时为空的静态链表，无数据结点，头结点的游标为-1
    s[0].cur = -1;
}


// 分配一个空闲节点
int MallocList(SLinkList s){
    int i = s[0].cur;  // 当前数组第一个元素的cur存的值就是要返回的第一个备用空间的下标
    // 如果备用区中还有可用空间那么就进行分配（更改备用区头指针的指向）
    if(s[1].cur)
        s[1].cur = s[i].cur; // 把下一个分量用来做备用
    return i;
}


// 释放回静态链表到空闲链表中
// 即插入到备用链表第一个结点前
void FreeList(SLinkList s, int k) {
    // 先把要释放的第k个节点指向保存到第一个空闲节点的cur
    s[k].cur = s[0].cur;
    // 再让代表第一个空闲节点指向k
    s[0].cur = k;
}


// 查询链表长度
int ListLength(SLinkList s){
    int i, j=0;
    i = s[MAX_SIZE-1].cur;   //i指向第一个结点

    while (i){    //最后一个结点的指针域为空，结束循环
        ++j;
        i = s[i].cur;
    }
    return j;
}


// 插入数据到链表，头插法
int ListInsertHead(SLinkList s, int value) {

    int i = MallocList(s);//申请空间
    if(i == 0)//如果为零表示申请空间失败
    {
        printf("申请节点空间失败.\n");
        return ERROR;
    }

    s[i].data = value;
    //如果之前静态链表中无数据结点，需要更改头结点的指向
    if(s[0].cur == -1)
    {
        s[i].cur = -1;
        //space[0].cur = i;
    }
    else //如果之前已经有数据结点那么直接头插
    {
        s[i].cur = s[0].cur;
    }
    s[0].cur = i;
    return OK;
}



// 删除链表中第i个位置的元素（从1开始）
int ListDelete(SLinkList s, int i, int *e) {
    // 检查位置是否合法
    if (i < 1 || i > ListLength(s)) return ERROR;

}



//查找元素实现


// 打印静态链表
void DisplayList(SLinkList s) {
    int i = s[0].cur;//从第一个数据结点开始搜索
    while (i != -1)//将所有的数据结点打印
    {
        printf("%d-->", s[i].data);
        i = s[i].cur; // p = p->next;
    }
    printf("Nul.\n");
}






int main() {
    SLinkList s;

    // 初始化链表
    InitList(s);

    // 插入元素
    ListInsertHead(s, 10);
    ListInsertHead(s, 21);
    ListInsertHead(s, 13);
    ListInsertHead(s, 16);
    ListInsertHead(s, 11);
    DisplayList(s);

    // 删除元素
    int rec = 0;
    ListDelete(s,3, &rec);
    printf("%d\n", rec);
    DisplayList(s);

    return 0;
}
