#include<stdio.h>
#include<stdlib.h>

//遍历数组
void  mm_ergodicArray(int* array, int array_size) {
    for (int i = 0; i < array_size; i++)
        printf("%d ", array[i]);
    printf("\n");
}

// 获取数组中的最大值
int getMax(int arr[], int n) {
    int max = arr[0];
    for (int i = 1; i < n; i++) {
        if (arr[i] > max) {
            max = arr[i];
        }
    }
    return max;
}

// 计数排序，用于基数排序的每一位
void countingSort(int arr[], int n, int exp) {
    int* output = (int*)malloc(n * sizeof(int)); // 输出数组
    int count[10] = { 0 }; // 计数数组，因为我们是十进制

    // 统计每个数字在当前位上的出现次数
    for (int i = 0; i < n; i++) {
        int index = (arr[i] / exp) % 10;
        count[index]++;
    }

    // 计算每个数字的起始位置（即前缀和）
    for (int i = 1; i < 10; i++) {
        count[i] += count[i - 1];
    }

    // 根据计数数组将元素放到输出数组的正确位置
    for (int i = n - 1; i >= 0; i--) {
        int index = (arr[i] / exp) % 10;

        //count[index]表示前面有几个整数（包含index）
        output[count[index] - 1] = arr[i];  //数组下标从0开始，要-1.

        //count[index]个数减1，计算下次在来index，向前放
        count[index]--;
    }

    // 将排序后的数组复制回原数组
    for (int i = 0; i < n; i++) {
        arr[i] = output[i];
    }

    // 释放输出数组的内存
    free(output);
}

// 基数排序
void radixSort(int arr[], int n) {
    int max = getMax(arr, n); // 获取数组中的最大值

    // 对每一位（个，十，百）进行计数排序
    for (int exp = 1; max / exp > 0; exp *= 10) {
        countingSort(arr, n, exp);
    }
}

// 主函数
int main() {
    int array_radix[] = { 170, 45, 75, 90, 802, 24, 2, 66 };
    int array_rad_size = sizeof(array_radix) / sizeof(array_radix[0]);
    mm_ergodicArray(array_radix, array_rad_size);
    radixSort(array_radix, array_rad_size);
    printf("Sorted array: \n");
    mm_ergodicArray(array_radix, array_rad_size);
    return 0;
}
