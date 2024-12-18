#include <stdio.h>
#include <stdlib.h>

#define INITIAL_SIZE 10
#define LISTINCREMENT 5
#define OK 1
#define ERROR 0
#define OVERFLOW -1


// 线性表结构体
typedef struct {
    int *data;      // 存储数据的动态数组
    int length;       // 当前元素数量
    int listsize;   // 数组的容量
} ADT;


//结构初始化操作,以存储的int线性表为例子
void initArray(ADT *arr){
    arr->data = (int *) malloc (INITIAL_SIZE * sizeof(int));
    if (arr->data == NULL) {
        perror("Failed to initialize array");
        exit(EXIT_FAILURE);
    }
    arr->length = 0;
    arr->listsize = INITIAL_SIZE;
}



// 插入操作
int ListInsert(ADT *L, int i, int value) {
    if (i < 1 || i > L->length + 1) return ERROR;

    if (L->length >= L->listsize) { // 当前存储已满，增加分配
        // L->arr 是指向当前存储空间的指针，L.listsize + LISTINCREMENT 是新的存储容量。LISTINCREMENT 是每次扩展时增加的容量。sizeof(Eint) 是要插入元素类型的大小。
        int *newbase = (int *) realloc(L->data, (L->listsize + LISTINCREMENT) * sizeof(int));
        if (!newbase) return OVERFLOW;
        L->data = newbase;
        L->listsize += LISTINCREMENT;
    }

    // q 是指向插入位置的指针。由于顺序表的索引是从0开始的，插入位置 i 需要减去1
    int *q = &(L->data[i - 1]);
    // 循环从顺序表的末尾开始，逐步将每个元素向右移动一个位置，为新元素腾出位置p
    // 是一个指向顺序表最后一个元素的指针，循环直到 p 移动到插入位置之前的位置。
    for (int *p = &(L->data[L->length - 1]); p >= q; --p) {
        *(p + 1) = *p;
    }

    *q = value;  // 在插入位置 q 插入新的元素 e
    ++L->length;
    return OK;
}


// 删除操作
int ListDelete(ADT *arr, int i, int *result){
    if((i < 1) || (i > arr->length)){
        return ERROR;
    }

    int *p, *q;
    p = &(arr->data[i - 1]);    // p为被删除元素的位置
    *result = *p;     // 被删除元素的值的地址赋给 result的地址，实现传递
    q = arr->data + arr->length - 1; // 表尾元素的位置

    // 插入从前往后移动，删除从后往前移动
    // 被删除元素之后的元素左移
    ++p;
    for (; p <= q; ++p) {
        *(p - 1) = *p;
    }

    --arr->length;   // 表长减 1

    return OK;
}



int main() {
    ADT arr;
    initArray(&arr);

    // 测试插入
    ListInsert(&arr, 1, 5);
    ListInsert(&arr, 2, 10);
    ListInsert(&arr, 3, 15);
    ListInsert(&arr, 2, 12);
    ListInsert(&arr, 4, 20);

    // 打印结果
    for(int i = 0; i < arr.length; i++) {
        printf("%d ", arr.data[i]);
    }
    printf("\n");

    int result = 0;
    ListDelete(&arr,3,&result);
    for(int i = 0; i < arr.length; i++) {
        printf("%d ", arr.data[i]);
    }
    printf("\n");
    printf("%d\n",result);

    free(arr.data);
    return 0;
}