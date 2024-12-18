#include <stdio.h>
#include <stdlib.h>

#define MAX_ARRAY_DIM 9
const int ERROR = -1;
const int OVERFLOW = 1;
const int OK = 0;

typedef struct{
    int *base;        // 数组元素基址
    int dim;          // 数组维数
    int *bounds;      // 数组维界基址（各维度大小）
    int *constants;    // 数组映像函数常量基址
} Array;

int InitArray(Array *array, int dim, int *bounds){
    // 检查维数是否合法
    if (dim < 1 || dim > MAX_ARRAY_DIM) return ERROR;

    // 设置数组维数
    array->dim = dim;
    // 分配维界数组空间
    array->bounds = (int *)malloc(dim * sizeof(int));
    if (!array->bounds) exit(OVERFLOW);  // 内存分配失败

    // 传入的各维度大小 bounds[i] 依次拷贝到 array->bounds[i] 中，确定好了多维数组每个维度的边界大小情况
    for (int i = 0; i < dim; i++) {
        array->bounds[i] = bounds[i];
    }

    // 遍历各维度大小，将它们累乘，得到多维数组所包含的元素总个数
    int totalSize = 1;
    for (int i = 0; i < dim; i++) {
        totalSize *= bounds[i];
    }

    array->base = (int *)malloc(totalSize * sizeof(int));  // 分配数组空间
    if (!array->base) exit(OVERFLOW);  // 内存分配失败

    // constants存储用于计算多维索引到一维内存地址映射的常量，方便后续元素的访问和管理。
    array->constants = (int *)malloc(dim * sizeof(int));
    if (!array->constants) exit(OVERFLOW);  // 内存分配失败

    // 计算映像函数常量（将多维索引（比如访问二维数组时的 a[i][j] 形式的索引）准确地转换为对应的一维内存地址）
    array->constants[dim - 1] = 1;   // 最后一维初始化为1
    // 从倒数第二维向前遍历，当前维度的常量等于下一维度的常量乘以当前维度的大小
    for(int i = dim - 2; i >= 0; i--){
        array->constants[i] = array->constants[i + 1] * array->bounds[i + 1];
    }

    return OK;
}


int Locate(Array *array, int *indices){
    // indices对应的是每个维度的坐标
    int offset = 0;
    for(int i = 0; i < array->dim; i++){
        offset += indices[i] * array->constants[i];  // 线性下标计算
    }
    return offset;
}


// 获取元素
int GetElement(Array *array, int *indices) {
    int index = Locate(array, indices);  // 计算线性下标
    return array->base[index];  // 返回元素值
}


// 设置元素
void SetElement(Array *array, int *indices, int value) {
    int index = Locate(array, indices);  // 计算线性下标
    array->base[index] = value;  // 设置值
}


// 打印数组元素
void PrintArray(Array *array) {
    int *indices = (int *)malloc(array->dim * sizeof(int));
    int totalSize = 1;
    for (int i = 0; i < array->dim; i++) {
        totalSize *= array->bounds[i];  // 计算数组元素总数
    }
    for (int i = 0; i < totalSize; i++) {
        int temp = i;
        for (int j = array->dim - 1; j >= 0; j--) {
            indices[j] = temp % array->bounds[j];  // 计算当前元素的下标
            temp /= array->bounds[j];
        }
        printf("Element at [");
        for (int j = 0; j < array->dim; j++) {
            printf("%d", indices[j]);
            if (j < array->dim - 1) printf(", ");
        }
        printf("] = %d\n", array->base[i]);  // 打印当前元素
    }
    free(indices);  // 释放临时数组
}

// 释放数组
void FreeArray(Array *array) {
    free(array->base);       // 释放数据区
    free(array->bounds);     // 释放维界数组
    free(array->constants);  // 释放常量数组
}




int main() {
    Array array;  // 定义数组结构
    int bounds[MAX_ARRAY_DIM] = {2, 3, 4};  // 设定数组维度范围 (2 x 3 x 4)

    // 初始化数组
    if (InitArray(&array, 3, bounds) == ERROR) {
        printf("Array initialization failed.\n");
        return -1;
    }

    // 设置元素
    int indices1[] = {1, 2, 3}; // 对应位置 (1, 2, 3)
    SetElement(&array, indices1, 42);  // 设置元素为 42

    int indices2[] = {0, 0, 0}; // 对应位置 (0, 0, 0)
    SetElement(&array, indices2, 99);  // 设置元素为 99

    // 获取元素
    int value = GetElement(&array, indices1);
    printf("Element at (1, 2, 3): %d\n", value);  // 应该输出 42

    // 打印数组元素
    PrintArray(&array);

    // 释放数组资源
    FreeArray(&array);
    return 0;  // 程序结束
}