#include <stdio.h>
#include <stdlib.h>

typedef int LTDataType;   // 数据类型

typedef struct ListNode{
    struct ListNode* prev;    // prev为结点中的指向前一个结点的指针
    struct ListNode* next;    // next 为指针中的指向后一个结点的指针
    LTDataType data;          // 数据
}ListNode;


// 动态申请一个结点
ListNode* ApplyListNode(LTDataType x){
    ListNode* newNode = (ListNode*)malloc(sizeof(ListNode));
    if(newNode == NULL){
        printf("分配内存失败\n");
        exit(-1);
    }
    newNode->prev = newNode->next = NULL;
    newNode->data = x;
    return newNode;
}


// 创建头结点进行初始化
ListNode* ListInit(){
    ListNode* plist = ApplyListNode(0); // 头结点中的数据初始化为 0
    plist->prev = plist->next = plist;
    return plist;
}


// 尾插
void ListPushBack(ListNode* plist,LTDataType x){
    ListNode* newNode = ApplyListNode(x);
    // 双向链表，代表头指针的prev
    ListNode* tail = plist->prev;
    // 头指针的prev指向原来最后一个节点，而现在尾插，它的next需要指向新节点
    tail->next = newNode;
    // 新节点的prev指向原来最后一个节点，next需要指向头节点
    newNode->prev = tail;
    newNode->next = plist;
    // 代表头指针的prev指向插入的节点（最后一个节点）
    plist->prev = newNode;
}


// 尾删
void ListPopBack(ListNode* plist){
    if (plist->next == plist) {
        return;  // 链表为空，直接返回
    }
    // tail指针代表头节点的prev，指向最后一个节点
    ListNode* tail = plist->prev;
    // 删除最后一个元素，那么新的最后一个元素就是要删除的元素的prev
    ListNode* newTail = tail->prev;
    // 新尾端元素的next指向头指针
    newTail->next = plist;
    // 头指针的prev指向新尾端元素
    plist->prev = newTail;
    free(tail);
}


// 头插
void ListPushFront(ListNode* plist, LTDataType x) {
    ListNode* newNode = ApplyListNode(x);
    // 获取当前链表的第一个节点（即头节点plist的下一个节点）
    ListNode* first = plist->next;
    // 将新节点的next指针指向first，prev指向头节点
    newNode->next = first;
    newNode->prev = plist;
    // first的prev指针指向新节点
    first->prev = newNode;
    // 头节点plist的next指针指向新节点
    plist->next = newNode;
}


// 头删
void ListPopFront(ListNode* plist) {
    if (plist->next == plist) {
        return;  // 链表为空，直接返回
    }
    // 获取头节点plist的下一个节点（即当前链表的第一个节点）
    ListNode* first = plist->next;
    // 获取first的下一个节点，记为second。
    ListNode* second = first->next;
    // 把头节点plist的next指针指向second
    plist->next = second;
    // 让second的prev指针指向头节点plist
    second->prev = plist;
    // 跳过了first，实现删除
    free(first);
}


// 查找元素，返回找到的节点指针，如果没找到返回NULL
ListNode* ListFind(ListNode* plist, LTDataType x) {
    ListNode* cur = plist->next;
    while (cur!= plist) {
        if (cur->data == x) {
            return cur;
        }
        cur = cur->next;
    }
    return NULL;
}


// 在pos位置之前进行插入
void ListInsert(ListNode* pos, LTDataType x) {
    ListNode* newNode = ApplyListNode(x);
    // 获取pos节点的前一个节点，记为prev
    ListNode* prev = pos->prev;
    // 将prev的next指针指向新节点
    prev->next = newNode;
    // 新节点的prev指针指向prev
    newNode->prev = prev;
    // 新节点的next指针指向pos
    newNode->next = pos;
    // 最后把pos的prev指针指向新节点
    pos->prev = newNode;
}

// 删除pos位置的结点
void ListErase(ListNode* pos) {
    if (pos == NULL) {
        return;
    }
    // 获取pos节点的前一个节点，记为prev
    ListNode* prev = pos->prev;
    // 再获取pos节点的后一个节点，记为next
    ListNode* next = pos->next;
    // 让前一个结点的next指向next，prev指向prev，这样略过了pos结点，实现删除
    prev->next = next;
    next->prev = prev;
    free(pos);
}

// 打印链表
void ListPrint(ListNode* plist) {
    ListNode* cur = plist->next;
    while (cur!= plist) {
        printf("%d ", cur->data);
        cur = cur->next;
    }
    printf("\n");
}



int main() {
    ListNode* list = ListInit();
    ListPushBack(list, 1);
    ListPushBack(list, 2);
    ListPushBack(list, 3);
    ListPushFront(list, 0);
    ListPrint(list);
    ListNode* found = ListFind(list, 2);
    if (found) {
        ListInsert(found, 10);
    }
    ListPrint(list);
    ListPopBack(list);
    ListPrint(list);
    ListPopFront(list);
    ListPrint(list);
    ListNode* toErase = ListFind(list, 10);
    if (toErase) {
        ListErase(toErase);
    }
    ListPrint(list);
    return 0;
}
