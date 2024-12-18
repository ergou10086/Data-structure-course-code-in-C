#include <stdio.h>
#include <string.h>
#include <assert.h>
#include <stdlib.h>

void GetNext(char* arr2, int* next){
    // i 为当前 字串 的位置，k 为前缀的长度
    int i = 0;
    int k = -1;
    int len2 = strlen(arr2);
    // 一样，第一个字符对应的值为 -1，第二个字符对应 0
    next[0] = -1;

    // 没遍历完整个模式串，就遍历
    while (i < len2){
        // 模式串中处于开头或者说明当前位置 i 和 k 指向的字符相等
        if (k == -1 || arr2[i] == arr2[k]){
            k++, i++;
            // 后一位的字符 arr2[i] 与 arr2[k] 仍然相等
            // 按照传统的只计算简单 next 数组的方法，可能会逐步回溯多次来确定 next 数组值
            // 进入第一个if语句后向后一位的字符该arr2[i]与arr2[k]仍然相等则直接一次性回溯到位
            if (arr2[i] == arr2[k]){
                // 可以直接利用已经计算好的 next[k] 的值来快速确定 next[i] 的值
                next[i] = next[k];
            }
            else{     //arr2[i] ！= arr2[k]
                next[i] = k; //不用多次回溯，跟next数组一样
            }
        }
        else{
            // 失配规则和next数组一样
            k = next[k];
        }
    }
}

// 倒是一样
int KMP(char* arr1, char* arr2){
    assert(arr1 && arr2);
    int len1 = strlen(arr1);
    int len2 = strlen(arr2);
    if (len2<0 || len2>len1)
    {
        return -1;
    }
    if (len1 == 0 || len2 == 0)
    {
        return -1;
    }
    int* next = (int*)malloc(sizeof(int) * len2);
    GetNext(arr2, next);
    int i = 0;
    int j = 0;
    while (j == -1 || i < len1 && j < len2){
        if (arr1[i] == arr2[j])
        {
            i++;
            j++;
        }
        else
        {
            j = next[j];
        }
    }
    if (j >= len2)
    {
        return i - j;
    }
    return -1;
}


int main(){
    char arr1[] = "abababcabc";
    char arr2[] = "abcabc";
    printf("%d", KMP(arr1, arr2));
    return 0;
}
