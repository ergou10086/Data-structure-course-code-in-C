#include <stdio.h>
#include <string.h>
#include <assert.h>
#include <stdlib.h>

// arr2为子串
// 每次模式匹配失败后，计算模式串向后移动的距离是 KMP 算法中的核心部分。匹配失败后模式串移动的距离只与模式串本身有关系。
// next数组用于存储模式串中每个字符对应指针 j 重定向的位置
// 计算方式，next 值的计算方式是，取该字符前面的字符串（不包含自己），其前缀字符串和后缀字符串相同字符的最大个数就是该字符对应的 next 值。
void GetNext(char* arr2, int* next){
    // i 为当前 字串 的位置，k 为前缀的长度
    int i = 0;
    int k = -1;
    int len2 = strlen(arr2);
    // 模式串中第一个字符对应的值为 -1，第二个字符对应 0
    next[0] = -1;
    while (i < len2){
        // k==-1时有两种情况：第一种是一开始k就为-1，第二种是k=-1是不能再回溯。
        if (k == -1 || arr2[i] == arr2[k]){
            k++;   // 若相等则k一定只加1，子串指针后移一位
            i++;   // 子串往后移一位里放next的值
            next[i] = k;  // 放入next的值
        }
        else{
            // 如果发现了失配，那么能匹配的大小只能是失配位置x2-1长度，也就是j=next[j]
            k = next[k]; // 字符不同则回溯
        }
    }
}


// 模式串与主串的匹配函数
// arr1为主串，arr2为字串
int KMP(char* arr1, char* arr2){
    assert(arr1 && arr2); // 保证传入的指针不是空指针
    int len1 = strlen(arr1);
    int len2 = strlen(arr2);

    // 两种不可能的情况
    if (len2 < 0 || len2 > len1){
        return -1;
    }
    if (len1 == 0 || len2 == 0){
        return -1;
    }

    // 为next数组动态开辟空间，求next
    int* next = (int*)malloc(sizeof(int) * len2);
    GetNext(arr2, next);

    // 其中 i 用于遍历主串 arr1，j 用于遍历模式串 arr2
    int i = 0, j = 0;
    while (j == -1 || i < len1 && j < len2){
        // 当主串当前位置 i 处的字符和模式串当前位置 j 处的字符相等时，说明这两个位置的字符匹配上了，此时就将 i 和 j 都向后移动一位
        if (arr1[i] == arr2[j]){
            i++;
            j++;
        }
        else{
            // 不相等则回溯子串，主串不动
            j = next[j];
        }
    }
    // 当模式串的索引 j 已经遍历完整个模式串
    if (j >= len2){
        // 返回主串与字串开始匹配到成功的开始位置
        return i - j;
    }
    //子串与主串没有可匹配的字符串
    return -1;
}



int main(){
    char arr1[] = "abababcabc";
    char arr2[] = "abcabc";
    printf("%d", KMP(arr1, arr2));
    return 0;
}

