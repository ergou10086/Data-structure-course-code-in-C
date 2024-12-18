#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct {
    char *ch;      //按串长分配存储区，ch指向串的基地址
    int length;
}DString;

// 初始化动态字符串
void InitDString(DString *str, const char *initStr) {
    str->length = 0;  // 初始化长度为0
    str->ch = NULL;   // 初始化字符串指针为空

    if(initStr != NULL){
        while(initStr[str->length] != '\0'){
            str->length++;
        }
        // 分配内存
        str->ch = (char *)malloc((str->length + 1) * sizeof(char));
        // 手动复制
        if(str->ch != NULL){
            for(int i = 0; i < str->length; i++){
                str->ch[i] = initStr[i];
            }
            str->ch[str->length] = '\0';
        }

    }
}


// 销毁动态字符串
void DestroyDString(DString *str) {
    if (str->ch != NULL) {
        free(str->ch); // 释放分配的内存
        str->ch = NULL; // 避免悬空指针
    }
    str->length = 0; // 重置长度
}


// 串连接
void ConcatDString(DString *dest, const DString *src) {
    if (src->length == 0) return; // 如果源字符串为空，直接返回
    int newLength = dest->length + src->length; // 计算新字符串的长度
    char *newCh = (char *)realloc(dest->ch, (newLength + 1) * sizeof(char)); // 重新分配内存
    if (newCh != NULL) {
        dest->ch = newCh; // 只在成功时更新指针
        for (int i = 0; i < src->length; i++) {
            dest->ch[dest->length + i] = src->ch[i]; // 正确地拼接字符
        }
        dest->ch[newLength] = '\0'; // 结束字符
        dest->length = newLength; // 更新长度
    }
}


// 用sub串返回s的第pos个字符起长度为len的字串
char *sub(DString *s, int pos, int len){
    // 参数无效
    if(pos < 0 || pos >= s->length || len <= 0){
        return NULL;
    }
    // 确保子串不超出范围
    if(pos + len > s->length){
        len = s->length - pos;
    }
    char *substring = (char *) malloc((len + 1) * sizeof (char));
    if(substring == NULL){
        return NULL;
    }
    for(int i = 0; i < len; i++){
        substring[i] = s->ch[pos + i];
    }
    substring[len] = '\0';
    return substring;
}


// 复制动态字符串
void CopyDString(DString *dest, const DString *src) {
    // 释放目标字符串的内存
    if (dest->ch != NULL) {
        free(dest->ch);
    }

    // 复制源字符串的长度
    dest->length = src->length;

    // 如果源字符串长度为0，设置目标字符串为空
    if (src->length == 0) {
        dest->ch = NULL;
    } else {
        // 分配内存给目标字符串
        dest->ch = (char *) malloc((dest->length + 1) * sizeof(char)); // +1 为了'\0'
        if (dest->ch == NULL) {
            // 内存分配失败
            perror("Failed to allocate memory");
            exit(EXIT_FAILURE);
        }

        // 复制源字符串
        for (int i = 0; i < src->length; i++) {
            dest->ch[i] = src->ch[i];
        }
        dest->ch[dest->length] = '\0'; // 添加字符串结束符
    }
}





int main() {
    DString str1;
    InitDString(&str1, "Hello, "); // 初始化 str1
    printf("str1: %s\n", str1.ch);

    DString str2;
    InitDString(&str2, "World!"); // 初始化 str2
    printf("str2: %s\n", str2.ch);

    ConcatDString(&str1, &str2); // 连接 str1 和 str2
    printf("After concatenation, str1: %s\n", str1.ch);


    DString str3;
    CopyDString(&str3, &str1); // 复制 str1 到 str3
    printf("str3 (copy of str1): %s\n", str3.ch);


    DestroyDString(&str1); // 销毁 str1
    DestroyDString(&str2); // 销毁 str2
    DestroyDString(&str3); // 销毁 str3

    return 0;
}