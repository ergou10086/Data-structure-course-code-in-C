#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAXBIT      100
#define MAXVALUE  10000
#define MAXLEAF     30
#define MAXNODE    MAXLEAF*2 -1
#define MAXSIZE 5

typedef struct{
    int weight;//权重
    int parent, lch, rch;//双亲，左孩子，右孩子
}HTNode, *HuffmanTree;   // HuffmanTree 是 HTNode 类型的指针，指向哈夫曼树的根节点

// j,k接收两个最小权重在数组中的下标
int j = 0;
int k = 0;


// 配合qsort()函数的比较函数,排序权重值的函数，选择最小权重节点时找到最小的两个权重。
int cmp(const void *e1, const void *e2){
    if(*(int*)e1 - *(int*)e2 > 0)  return 1;
    else if(*(int*)e1 - *(int*)e2 < 0)  return -1;
    else return 0;
}



// 找出权重最小的二个根结点在ＨＴ数组中的位置，选择两个权重最小的节点
int Select(HuffmanTree HT, int n){
    int p = 0;       // 用于控制数组arr，按顺序存储数据
    int arr[MAXSIZE] = {0};  // 存储当前哈夫曼树中所有没有父节点的节点的权重。
    int count = 0;   // 用来记录arr数组中，有几个值需要排序，也就是当前有效节点的数量。

    // 首先，遍历整个树，收集所有没有父节点的节点的权重（即未参与合并的节点）。
    for(int i = 1; i <= n; i++){
        // 必须是有权重值的根结点，才会被加入到arr数组当中
        if(HT[i].parent == 0 && HT[i].weight != 0){
            arr[++p - 1] = HT[i].weight;
            // arr有效元素个数+1，arr数组中初始化的0，不算有效元素
            count++;
        }
    }

    // 使用 qsort 对 arr 数组中的权重进行排序，找到最小的两个权重。
    qsort(arr, count, sizeof(int), cmp);

    // 遍历 HT 数组（哈夫曼树的节点数组）来获取这两个最小权重节点的下标，分别存储在 j 和 k 中。
    for(int i = 1; i <= n; i++){
        if(HT[i].weight == arr[0]){
            j = i;
            break;
        }
    }
    for(int i = 1; i <= n; i++){
        //arr[1]是第二小的元素，且要保证arr[0]=arr[1]时,选取的两个下标不相同
        if(HT[i].weight == arr[1] && i != j){
            k = i;
            break;
        }
    }

    return 0;
}

// 构造哈夫曼树
void CreatHuffmanTree(HuffmanTree* HT, int n, int* arr){
    int m = 0;
    // 一个叶子节点或者没有，就不用构造
    if(n <= 1) return;

    // 分配一个大小为 2n-1 的哈夫曼树节点数组（从索引 1 开始）。对所有节点的权重、父节点、左右孩子进行初始化为 0。
    // 有n个叶子，树就有2n-1个结点，0号位置不用，所以需要2n个结点大小
    m = 2 * n - 1;
    *HT = malloc(sizeof(HTNode)*(m+1));

    // 将2n-1个元素初始化，lch,rch,parent设置为0
    for(int i = 1; i <= m+1; i++){
        (*HT)[i].lch = 0;
        (*HT)[i].rch = 0;
        (*HT)[i].parent = 0;
        (*HT)[i].weight = 0;
    }

    // 设置叶子节点的weight值
    for(int i = 1; i <= n; i++){
        (*HT)[i].weight = arr[i - 1];
    }

    // 创建哈夫曼树，每次合并最小的两个节点
    // 初始有n个根结点，就要新产生n-1个结点，循环一次产生一个
    for(int i = 1; i < n; i++){
        Select(*HT, m+1);  // 选择出两个最小权重的节点j，k
        // ＨＴ数组中有n个根结点，那么新生成的根结点下标从n+1开始
        // 新节点的左孩子右孩子指向j，k
        (*HT)[n+i].lch = j;
        (*HT)[n+i].rch = k;
        // 设置新根结点的权重值为两孩子权重值之和
        (*HT)[n+i].weight = (*HT)[j].weight + (*HT)[k].weight;
        // 新根结点的下标值为最小权值的两个结点的双亲
        (*HT)[j].parent = n+i;
        (*HT)[k].parent = n+i;
    }
}


// 获取每个叶子节点的哈夫曼编码
void GetHC(HuffmanTree HT, int n, char** HC[]) {
    // 创建一个临时数组，来存放一个叶子节点的哈夫曼编码，注意要多分配一个字节给'\0'
    char* TempArr = (char*)malloc(n + 1);
    // 临时数组最后一位设为结束符
    TempArr[n] = '\0';
    // 给传进来的二维数组申请空间，并把这个空间的地址赋给ＨＣ
    *HC = malloc(sizeof(char*)*n);

    for (int i = 1; i <= n; i++) {
        // m是用来记录临时数组中，放进了几个字符．后面就知道用多大的空间来接收了．还可以控制临时数组存放第一个字符的起始位置
        int m = 0;
        // a控制当前循环的结点
        int a = i;
        while (HT[a].parent) {
            // 如果该结点是其双亲的左孩子，记录为0
            if (HT[HT[a].parent].lch == a)  TempArr[n - 1 - m++] = '0';
            // 如果该结点是其双亲的右孩子，记录为1
            if (HT[HT[a].parent].rch == a)  TempArr[n - 1 - m++] = '1';
            // 再定位在该结点的双亲，用于下次循环
            a = HT[a].parent;
        }
        // 根据m的值，可用直到临时数组有几个字符，然后准确的申请相应的空间
        (*HC)[i] = malloc(m + 1);
        // 使用strncpy进行字符串复制，并确保设置正确的长度，避免越界
        strncpy((*HC)[i], &TempArr[n - m], m);
        // 添加字符串结束符
        (*HC)[i][m] = '\0';
    }
    free(TempArr);   // 释放临时空间
}


// 哈夫曼编码翻译成字符串
// 首先以字符集对应的字符权重，创建哈夫曼树
void GetStr(HuffmanTree HT, int nums, char* arr2, char* arr3){
    //nums个叶子，就有2*nums-1个结点，根结点在ＨＴ数组中的下标为2*nums-1
    int n = 2 * nums - 1;
    int len = strlen(arr3);

    // 初始化解码的结果字符串
    char decodedStr[MAXSIZE];
    int decodedLen = 0;  // 解码后的字符个数

    // 读入arr3
    for(int i = 0; i < len; i++){
        // //读入的数据为1时，指向该结点的右孩子
        if(arr3[i] == '1') n = HT[n].rch;
        // 读入的数据为0时，指向该结点的左孩子
        else if(arr3[i] == '0') n = HT[n].lch;
        else return;

        // 当我们到达叶子结点时，说明我们解码出了一个字符
        if (HT[n].lch == 0 && HT[n].rch == 0) {
            // 叶子结点的索引即为字符的编号
            decodedStr[decodedLen++] = arr2[n - 1];  // 存储字符到结果字符串
            n = 2 * nums - 1;  // 回到根结点，准备解码下一个字符
        }
    }
    // 添加终止符
    decodedStr[decodedLen] = '\0';
    printf("解码后的字符串是: %s\n", decodedStr);  // 输出解码后的字符串
}



int main(){
    HuffmanTree HT;
    char** HC;   // 创建一个指针数组
    int arr1[5] = {3,4,5,6,7};
    char arr2[5] = {'a','b','o','u','t'};
    char* arr3 = "110000110111000110111110001001111110";
    int nums = sizeof(arr1) / sizeof(arr1[0]);  //字符集个数
    CreatHuffmanTree(&HT, nums, arr1);
    GetHC(HT, nums, &HC);
    GetStr(HT, nums, arr2, arr3);

    return 0;
}




