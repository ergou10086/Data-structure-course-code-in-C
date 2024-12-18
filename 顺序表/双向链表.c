#include <stdio.h>
#include <stdlib.h>

#define INITIAL_SIZE 10
#define LISTINCREMENT 5
#define OK 1
#define ERROR 0
#define OVERFLOW -1

typedef struct DLNode{
    int data;
    struct DLNode *prior;
    struct DLNode *next;
}DLNode, *DLinkList;   // DLinkList 是 DLNode* 类型的别名


// 初始化双向链表
DLinkList InitDLinkList() {
    DLinkList List = (DLinkList)malloc(sizeof(DLNode));
    if (!List) {
        printf("Memory allocation failed.\n");
        exit(OVERFLOW);
    }
    List->prior = NULL;
    List->next = NULL;
    return List;
}


// 头插法插入节点
int InsertHead(DLinkList List, int data) {
    DLinkList newNode = (DLinkList)malloc(sizeof(DLNode));
    if(!newNode){
        return OVERFLOW;
    }
    newNode -> data = data;
    newNode -> next = List ->next;
    newNode -> prior = List;

    // 如果插入的并非是第一个节点
    if(List -> next){
        // 需要把插入前的第一个节点的前驱指向要插入的节点
        List -> next -> prior = newNode;
    }
    // 再把头节点的后继连接到新节点上
    List -> next = newNode;

    return OK;
}


// 尾插法插入节点
int InsertTail(DLinkList List, int data) {
    DLinkList newNode = (DLinkList)malloc(sizeof(DLNode));
    if(!newNode){
        return OVERFLOW;
    }

    // tail 是一个临时指针，用来从链表头 L 开始遍历链表
    DLinkList tail = List;
    while (tail->next != NULL) {
        tail = tail->next;
    }

    newNode -> data = data;
    newNode -> next = NULL;
    newNode -> prior = tail;   //将新节点的 prior 指针指向当前的尾节点。
    tail -> next = newNode;   // 尾部节点的next指向新节点，实现闭口

    return OK;
}


// 根据序列位置插入
int InsertNextDnode(DLinkList List, int index, int value){
    if (index < 1) {
        return ERROR;  // 位置不合理，返回错误
    }
    DLinkList p = List;
    int count = 0;

    // 先找到要插入位置的前驱节点（也就是序号为index - 1的节点）
    while (p!= NULL && count < index - 1) {
        p = p->next;
        count++;
    }

    if (p == NULL) {
        return ERROR;  // 没找到对应位置的前驱节点，说明位置超出链表范围，返回错误
    }

    DLinkList newNode = (DLinkList)malloc(sizeof(DLNode));
    if(!newNode) return OVERFLOW;

    newNode->data = value;
    newNode->next = p->next;
    newNode->prior = p;
    if (p->next!= NULL) {
        p->next->prior = newNode;
    }
    p->next = newNode;

    return OK;
}


// 根据值删除节点
int DeleteNode(DLinkList List, int data) {
    // 定义一个指针p，指向头节点的next
    DLinkList p = List -> next;
    // 不断向后遍历，直到找到相同值的第一个节点，删除
    while (p != NULL && p->data != data) {
        p = p->next;
    }

    if (p == NULL) {
        return ERROR; // 节点未找到
    }

    // 找到节点了
    if (p->next) {
        p->next->prior = p->prior; // 如果节点 p 后面还有节点，则把p的下一个节点的前驱指针指向p节点的上一个节点
    }
    p -> prior -> next = p -> next;   // p节点的前一个结点的next指针，指向p的后一个结点，实现闭环，略过了p结点

    free(p); // 释放节点 p 的内存，实现删除
    return OK; // 删除成功，返回 OK
}


// 删除第 i 个节点并返回其值
int DeleteNodeAtIndex(DLinkList List, int index, int *value) {
    if (index <= 0) {
        return ERROR; // 索引无效
    }

    DLinkList p = List -> next; // 从链表头的下一个节点开始查找
    int i = 1; // 索引从 1 开始
    while (p != NULL && i < index) {
        p = p->next; // 遍历到第 index 个节点
        i++;
    }

    // 没有找到第 index 个节点
    if(p == NULL || i != index){
        return ERROR;
    }

    // 找到了，先将值存储到指针 value 指向的位置
    if (value != NULL) {
        *value = p->data;
    }

    if (p->next) {
        p->next->prior = p->prior; // 如果节点 p 后面还有节点，则把p的下一个节点的前驱指针指向p节点的上一个节点
    }

    if(p->prior){
        p->prior->next = p->next;  // 将节点 p 的前驱的 next 指针指向节点 p 的后继
    } else{   // 这里考虑到了删除第一个结点的情况，头节点的next指针指向第二个结点略过第一个几点
        List -> next = p -> next;
    }

    free(p);
    return OK;
}


// 查找第一个符合值结点的位置
int FindNode(DLinkList List, int data) {
    DLinkList p = List->next;
    int cur = 1;
    while (p != NULL) {
        if (p->data == data) {
            return cur;
        }
        p = p->next;
        cur++;
    }
    return ERROR; // 未找到节点
}


int FindNodeIndex(DLinkList List, int index) {
    DLinkList p = List->next;
    if (index < 1) return ERROR;  // 注意这里的index从1开始
    int cur = 1;
    while (p != NULL) {
        if (cur == index) {
            return p->data;  // 返回节点数据
        }
        cur += 1;
        p = p->next;  // 更新p指针
    }
    return ERROR;  // 没有找到
}



// 从头到尾打印链表
void PrintList(DLinkList List) {
    DLinkList p = List->next;
    while (p != NULL) {
        printf("%d ", p->data);
        p = p->next;
    }
    printf("\n");
}


// 从尾到头打印链表
void PrintListReverse(DLinkList List) {
    DLinkList p = List;
    // 先从头走到尾
    while(p->next != NULL){
        p = p -> next;
    }
    // 再从后向前打印
    while (p != List) {
        printf("%d ", p->data);
        p = p->prior;
    }
    printf("\n");
}


// 释放掉双向链表
void FreeList(DLinkList L) {
    // 先从头走到尾
    DLinkList p = L->next;
    while (p != NULL) {
        // 一个个释放，先走一个再释放前面的
        DLinkList temp = p;
        p = p->next;
        free(temp);
    }
    free(L); // 释放头节点
}


// 返回双向链表的长度
int DListLength(DLinkList List){
    DLinkList p = List;
    int cut = 0;
    // 先从头走到尾
    while(p->next != NULL){
        p = p -> next;
        cut++;
    }
    return cut;
}


// 对于两个双向链表排序，1为正序，2为逆序
void SortList(DLinkList List, int order) {
    if (List == NULL || List->next == NULL) return; // 空链表或只有头节点

    int swapped;
    do{
        swapped = 0;
        DLinkList p = List -> next;
        while (p != NULL && p->next != NULL) {
            // 双指针，定义一个q始终在p的前面，为了查看是否满足交换情况，类似冒泡排序
            DLinkList q = p -> next;
            if ((order == 1 && p->data > q->data) || (order == 2 && p->data < q->data)) {
                int temp = p->data;
                p->data = q->data;
                q->data = temp;
                swapped = 1;
            }
            p = p -> next;
        }
    }while(swapped);
}


// 对于两个双向链表，合并并去重
DLinkList MergeAndUnique(DLinkList list1, DLinkList list2) {
    //新开一个链表存结果
    DLinkList mergedList = InitDLinkList();
    DLinkList p1 = list1->next;
    DLinkList p2 = list2->next;

    // 插入 list1 的所有节点
    while (p1 != NULL) {
        InsertTail(mergedList, p1->data);
        p1 = p1->next;
    }

    // 插入 list2 的所有节点
    while (p2 != NULL) {
        InsertTail(mergedList, p2->data);
        p2 = p2->next;
    }

    // 去重
    DLinkList p = mergedList->next;
    while (p != NULL) {
        // 双指针，定义一个q始终在p的前面，如果p没有找到与q相同的并且删除，那么p不动q一直动
        DLinkList q = p->next;
        while(q != NULL){
            if(p -> data == q -> data){
                DeleteNode(mergedList, q->data);
            }
            q = q -> next;
        }
        p = p -> next;
    }
    return mergedList;
}



int main(void){
    // 初始化双向链表
    DLinkList list = InitDLinkList();

    // 头插入测试
    InsertHead(list, 10);
    InsertHead(list, 15);
    InsertHead(list, 20);

    //尾插入测试
    InsertTail(list, 25);
    InsertTail(list, 30);
    InsertTail(list, 35);

    // 打印测试
    PrintList(list);
    PrintListReverse(list);

    // 返回长度测试
    int le = DListLength(list);
    printf("%d\n", le);

    // 删除测试
    DeleteNode(list, 20);
    PrintList(list);

    // 查找测试
    int sp1 = FindNode(list, 10);
    printf("%d\n", sp1);
    int sp2 = FindNodeIndex(list, 3);
    printf("%d\n", sp2);


    int rec1 = 0, rec2 = 0, rec3 = 0;
    DeleteNodeAtIndex(list, 3, &rec1);
    printf("%d\n",rec1);
    PrintList(list);


    // 删除首节点测试
    DeleteNodeAtIndex(list, 1, &rec2);
    printf("%d\n",rec2);
    PrintList(list);

    // 删除尾节点测试
    DeleteNodeAtIndex(list, 3, &rec3);
    printf("%d\n",rec3);
    PrintList(list);


    // 测试排序和合并
    DLinkList list1 = InitDLinkList();
    DLinkList list2 = InitDLinkList();

    // 插入数据到 list1 和 list2...  14 16 18 22 25    54 47 52 14 16
    for(int i = 1; i <= 5; i++){
        int n;  scanf("%d", &n);
        InsertTail(list1, n);
    }
    for(int i = 1; i <= 5; i++){
        int n;  scanf("%d", &n);
        InsertTail(list2, n);
    }

    // 排序链表测试
    SortList(list1, 1); // 正序
    SortList(list2, 2); // 逆序
    PrintList(list1);
    PrintList(list2);

    // 合并并去重测试
    DLinkList merged = MergeAndUnique(list1, list2);
    PrintList(merged);
    PrintListReverse(merged);
    FreeList(merged);


    // 释放
    FreeList(list);

    return 0;
}