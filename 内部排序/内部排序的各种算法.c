#include <stdio.h>
#include <stdlib.h>

#define MAXSIZE 20

typedef int KeyType;
typedef int InfoType;


typedef struct{
    KeyType  key;     // 关键字项
    InfoType otherinfo; // 其他数据项
}RedType;    // 记录类型

typedef struct{
    RedType  r[MAXSIZE+1];  //r[0]闲置或作哨兵
    int       length;      // 顺序表长度
}SqList;    // 顺序表类型


// 打印顺序表中的元素，用于测试查看排序结果
void printList(SqList L) {
    for (int i = 1; i <= L.length; i++) {
        printf("%d ", L.r[i].key);
    }
    printf("\n");
}


// 插入排序
void InsertSort(SqList *list){
    int i, j;
    for(i = 2; i <= list->length; i++){
        // 存在一个元素在后面比他前面的大，需要排序,需要将它插入到前面已排序部分中合适的位置
        if(list->r[i].key < list->r[i - 1].key){
            // 将待插入元素暂存到哨兵位置
            list->r[0] = list->r[i];
            // 将当前位置（索引为i）的元素用它前一个元素（索引为i - 1）覆盖掉,腾出了当前位置来准备插入合适的元素。
            list->r[i] = list->r[i - 1];
            // 从当前元素的前一个位置（索引为i - 1）开始，向前逐个比较元素，如果比哨兵小，不断地把较大的元素往后移
            for(j = i - 1; list->r[0].key < list->r[j].key; --j){
                list->r[j + 1] = list->r[j];
            }
            list->r[j + 1] = list->r[0];
        }
    }
}



// 折半插入排序
void binaryInsertSort(SqList* l){
    for (int i = 1; i < l->length; i++){
        RedType temp = l->r[i];  // 暂存待插入的元素
        // 二分查找
        int left = 0, right = i - 1;
        // 二分查找合适的插入位置
        while (left <= right) {
            int mid = (left + right) / 2;
            if (l->r[mid].key > temp.key) {
                right = mid - 1;
            }
            else {
                left = mid + 1;
            }
        }
        int j;
        // [left,i-1]段的元素向后移动，腾出插入位置
        for (j = i; j >= left + 1; j--) {
            l->r[j] = l->r[j - 1];
        }

        l->r[left] = temp;  // 将暂存的元素插入到合适位置
    }
}



// 希尔排序
// 希尔排序是将数据分组，按照间隔为gap的数为一组，将每一组进行插入排序,复杂度不稳定
// 对给定间隔gap进行分组插入排序
void shell(SqList* l, int gap) {
    // 从间隔 gap 对应的位置开始遍历顺序表
    for (int i = gap; i < l->length; i++) {
        RedType temp = l->r[i];
        int j;
        // 在当前分组内进行插入排序
        for (j = i; j >= gap && l->r[j - gap].key > temp.key; j -= gap) {
            l->r[j] = l->r[j - gap];
        }
        l->r[j] = temp;
    }
}

// 希尔排序主函数
void shellSort(SqList* l) {
    int len = l->length;
    int gap = len / 2;  // 初始步长设置为长度的一半
    while (gap > 0) {
        shell(l, gap);  // 针对当前步长进行分组插入排序
        gap /= 2;  // 缩小步长
    }
}



// 冒泡排序
void bubbleSort(SqList* l) {
    // 外层 for 循环控制比较的轮数，一共需要进行 l->length - 1 轮比较,每一轮比较都能把当前未排序部分的最大元素 “浮” 到最后面
    for (int i = 0; i < l->length - 1; i++) {
        // 内层 for 循环用于在每一轮中相邻元素两两比较,如果发现前一个元素（l->r[j]）的关键字大于后一个元素（l->r[j + 1]）的关键字
        for (int j = 0; j < l->length - 1 - i; j++) {
            if (l->r[j].key > l->r[j + 1].key) {
                // 交换两个元素的位置
                RedType temp = l->r[j];
                l->r[j] = l->r[j + 1];
                l->r[j + 1] = temp;
            }
        }
    }
}



// 快速排序
// 划分函数，选择一个基准元素，将数组分为两部分，左边小于等于基准，右边大于基准
int partition(SqList* l, int low, int high) {
    RedType temp;
    KeyType pivot = l->r[low].key;  // 一般选子表第一个记录作枢轴记录
    // 从表的两端交替地向中间扫描
    while(low < high){
        // 右指针指向的比基准值大，序正确，high--向中间走
        while(low < high && l->r[high].key >= pivot){
            --high;
        }
        // 如果出现了右指针指向的元素小于基准值，需要调换顺序，和左指针指向的元素换位置
        temp = l->r[high];
        l->r[high] = l->r[low];
        l->r[low] = temp;

        // 左指针指向的比基准值小，序正确，low++向中间走
        while (low < high && l->r[low].key <= pivot) {
            low++;
        }
        // 如果出现了左指针指向的元素大于基准值，需要调换顺序，和右指针指向的元素换位置
        temp = l->r[low];
        l->r[low] = l->r[high];
        l->r[low] = temp;
    }
    return low;
}

// 改进版，用0号空间存储，把交换改为赋值
int partition2(SqList* l, int low, int high){
    KeyType pivot;
    l->r[0] = l->r[low];    // 用子表的第一个记录作枢轴记录
    pivot = l->r[low].key;  //枢轴记录关键字

    while(low < high){
        while(low < high && l->r[high].key >= pivot){
            --high;
        }
        l->r[low] = l->r[high];  // 将比枢轴记录小的记录放到低端

        while (low < high && l->r[low].key <= pivot) {
            ++low;
        }
        l->r[high] = l->r[low];//将比枢轴记录大的记录放到高端
    }
    l->r[low] = l->r[0];   //枢轴记录到位
    return low;    //返回枢轴位置
}

// 快速排序递归函数
void quickSortRecursive(SqList* l, int low, int high) {
    if (low < high) {
        // 通过一趟排序将要排序的数据分割成独立的两部分，其中一部分的所有数据都小于基准值，另一部分所有数据都大于基准值
        int pivotIndex = partition(l, low, high);
        // 这两部分再次递归直到有序
        quickSortRecursive(l, low, pivotIndex - 1);
        quickSortRecursive(l, pivotIndex + 1, high);
    }
}
void quickSortRecursive2(SqList* l, int low, int high) {
    if (low < high) {
        int pivotIndex = partition2(l, low, high);
        quickSortRecursive(l, low, pivotIndex - 1);
        quickSortRecursive(l, pivotIndex + 1, high);
    }
}

// 非递归版
// 交换顺序表中两个元素的位置
void swap(RedType* a, RedType* b) {
    RedType temp = *a;
    *a = *b;
    *b = temp;
}

// 划分函数，选择一个基准元素，将数组分为两部分，左边小于等于基准，右边大于基准
int partition3(SqList* l, int low, int high) {
    KeyType pivot = l->r[high].key;  // 选择最后一个元素作为基准
    int i = low - 1;
    for (int j = low; j < high; j++) {
        if (l->r[j].key <= pivot) {
            i++;
            swap(&l->r[i], &l->r[j]);
        }
    }
    swap(&l->r[i + 1], &l->r[high]);
    return i + 1;
}

// 快速排序非递归版
void quickSortNonRecursive(SqList* l) {
    int stack[MAXSIZE];  // 用数组模拟栈
    int top = -1;  // 栈顶指针初始化为 -1，表示栈为空

    stack[++top] = 0;
    stack[++top] = l->length - 1;

    while (top >= 0) {
        int high = stack[top--];
        int low = stack[top--];

        if (low < high) {
            int pivotIndex = partition3(l, low, high);

            // 将左半部分区间索引压入栈
            stack[++top] = low;
            stack[++top] = pivotIndex - 1;

            // 将右半部分区间索引压入栈
            stack[++top] = pivotIndex + 1;
            stack[++top] = high;
        }
    }
}


// 简单选择排序
void simpleSelectSort(SqList *l){
    // 外层for循环控制排序的轮数,一共需要进行l->length - 1轮
    // 每一轮先假设当前位置i的元素的最小的，记录为minIndex
    for (int i = 1; i < l->length; i++) {
        int minIndex = i;
        // 从i + 1位置开始往后遍历剩余元素
        for (int j = i + 1; j <= l->length; j++) {
            // 如果发现有比l->r[minIndex]更小的元素，更新
            if (l->r[j].key < l->r[minIndex].key) {
                minIndex = j;
            }
        }
        // 内层循环结束后，如果minIndex不等于i，说明找到了更小的元素，需要交换这两个元素的位置
        if (minIndex!= i) {
            RedType temp = l->r[i];
            l->r[i] = l->r[minIndex];
            l->r[minIndex] = temp;
        }
    }
}


// 堆排序相关函数
// 调整大根堆函数
// low 表示当前要调整的子树的根节点索引，也就是从这个节点开始，调整以它为根的子树使其满足大根堆性质。
// high 表示当前堆（也就是整个数组中参与堆操作的那部分元素）的最后一个元素的索引，用于界定调整范围。
void adjustHeap(SqList* l, int low, int high) {
    RedType rc = l->r[low];     // 保存根节点的值
    // i = 2 * low 表示从根节点 low 的左子节点开始
    // 每次循环 i *= 2 是为了不断获取下一层的子节点，对于完全二叉树，节点 i 的左子节点索引就是 2 * i
    for (int i = 2 * low; i <= high; i *= 2) {
        // 比较当前节点 i 的左子节点和右子节点的值大小
        if (i < high && l->r[i].key < l->r[i + 1].key) {
            // 如果右子节点i + 1更大，就将 i 加1 更新为右子节点的索引
            i += 1;
        }
        // 如果rc根节点的值大于等于当前比较的子节点的值，经满足大根堆性质了，直接 break 跳出循环。
        if (rc.key >= l->r[i].key) {
            break;
        }
        // 子节点的值更大，就将较大的子节点的值上移到根节点位置，同时更新索引
        l->r[low] = l->r[i];
        low = i;
    }
    // 最后将最初保存的根节点的值（rc）放到合适的位置
    l->r[low] = rc;
}

// 堆排序主函数
void heapSort(SqList* l) {
    // 将一个无序序列构建成大根堆，建堆是一个从下到上依次筛选的过程
    // 从最后一个非叶子节点开始，依次向前对每个非叶子节点调用调整堆的操作，直到整个序列满足大根堆的性质
    for (int i = l->length / 2; i > 0; i--) {
        // 对于完全二叉树，最后一个非叶子节点的索引可以通过 length / 2（向下取整）来计算
        adjustHeap(l, i, l->length);
    }

    // 输出堆顶元素后调整为新堆
    for (int i = l->length; i > 1; i--) {
        // 大根堆构建好后，堆顶元素（索引为 1）就是整个序列中的最大值
        // 此时将堆顶元素与堆中最后一个元素交换位置（也就是把最大值放到了它最终有序的位置）
        RedType temp = l->r[1];
        l->r[1] = l->r[i];
        l->r[i] = temp;
        // 然后把剩下的 n - 1 个元素重新调整成一个新的大根堆，重复这个过程，直到整个序列有序。
        adjustHeap(l, 1, i - 1);
    }
}


// 归并排序相关函数

// 合并两个已排序的子数组
void merge(SqList *L, int low, int mid, int high) {
    int i, j, k;
    int n1 = mid - low + 1;
    int n2 = high - mid;

    // 创建临时数组存放两个子数组
    RedType *L1 = (RedType *)malloc((n1 + 1) * sizeof(RedType));
    RedType *L2 = (RedType *)malloc((n2 + 1) * sizeof(RedType));

    // 将原数组中对应部分复制到临时数组
    for (i = 0; i < n1; i++)
        L1[i] = L->r[low + i];
    for (j = 0; j < n2; j++)
        L2[j] = L->r[mid + 1 + j];

    // 设置哨兵，方便后面比较
    L1[n1].key = 1000000;  // 这里假设一个较大值作为哨兵，实际应用可根据数据范围合理设置
    L2[n2].key = 1000000;

    i = 0;
    j = 0;
    k = low;
    // 合并两个临时数组到原数组中
    while (i < n1 && j < n2) {
        if (L1[i].key <= L2[j].key) {
            L->r[k] = L1[i];
            i++;
        } else {
            L->r[k] = L2[j];
            j++;
        }
        k++;
    }

    // 处理剩余元素（若有）
    while (i < n1) {
        L->r[k] = L1[i];
        i++;
        k++;
    }
    while (j < n2) {
        L->r[k] = L2[j];
        j++;
        k++;
    }

    free(L1);
    free(L2);
}

// 归并排序递归函数
void mergeSort(SqList *L, int low, int high) {
    if (low < high) {
        int mid = (low + high) / 2;
        mergeSort(L, low, mid);
        mergeSort(L, mid + 1, high);
        merge(L, low, mid, high);
    }
}


int main() {
    SqList list;
    list.length = 7;
    list.r[1].key = 5;
    list.r[2].key = 3;
    list.r[3].key = 4;
    list.r[4].key = 6;
    list.r[5].key = 2;
    list.r[6].key = 4;

    printf("排序前的顺序表元素: ");
    printList(list);

    InsertSort(&list);
    printf("插入排序后的顺序表元素: ");
    printList(list);

    SqList list2 = list;  // 复制一份用于折半插入排序测试
    binaryInsertSort(&list2);
    printf("折半插入排序后的顺序表元素: ");
    printList(list2);

    SqList list3 = list;  // 复制一份用于希尔排序测试
    shellSort(&list3);
    printf("希尔排序后的顺序表元素: ");
    printList(list3);

    SqList list4 = list;  // 复制一份用于冒泡排序测试
    bubbleSort(&list4);
    printf("冒泡排序后的顺序表元素: ");
    printList(list4);

    SqList list5 = list;  // 复制一份用于快速排序（递归版）测试
    quickSortRecursive(&list5, 1, list5.length);
    printf("快速排序（递归版）后的顺序表元素: ");
    printList(list5);

    SqList list6 = list;  // 复制一份用于快速排序（递归版）改进 测试
    quickSortRecursive2(&list6, 1, list5.length );
    printf("快速排序（递归版）改进 后的顺序表元素: ");
    printList(list6);

    SqList list7 = list;  // 复制一份用于快速排序（非递归版）测试
    quickSortNonRecursive(&list7);
    printf("快速排序（非递归版）后的顺序表元素: ");
    printList(list7);

    SqList list8 = list;  // 复制一份用于简单选择排序测试
    simpleSelectSort(&list8);
    printf("简单选择排序后的顺序表元素: ");
    printList(list8);

    SqList list9 = list;  // 复制一份用于堆排序测试
    heapSort(&list9);
    printf("堆排序后的顺序表元素: ");
    printList(list9);

    SqList list10 = list;  // 复制一份用于归并排序测试
    mergeSort(&list10, 1, list10.length);
    printf("归并排序后的顺序表元素: ");
    printList(list10);


    return 0;
}