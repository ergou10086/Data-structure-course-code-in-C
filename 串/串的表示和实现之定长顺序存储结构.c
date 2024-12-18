// 采用静态一维数组
#include <stdio.h>
#include <string.h>

#define MAX_LENGTH 100 // 定义串的最大长度

// 串的结构体定义
typedef struct {
    char str[MAX_LENGTH]; // 字符数组，用于存储字符串
    int length;           // 当前串的长度
} String;

// 初始化串
void initString(String *s) {
    s->str[0] = '\0'; // 设置为空串
    s->length = 0;    // 长度为0
}

// 输入串
void inputString(String *s) {
    printf("请输入字符串（最多%d个字符）：", MAX_LENGTH - 1);
    fgets(s->str, MAX_LENGTH, stdin); // 从标准输入读取字符串
    s->str[strcspn(s->str, "\n")] = '\0'; // 去掉换行符
    s->length = strlen(s->str); // 更新串的长度
}

// 输出串
void outputString(const String *s) {
    printf("当前字符串为：%s\n", s->str);
}

// 连接串
void concatString(String *s1, const String *s2) {
    // 检查连接后的长度是否超过最大限制
    if (s1->length + s2->length < MAX_LENGTH) {
        // 将s2的内容复制到s1的末尾
        int i = s1->length; // 从s1的末尾开始
        for (int j = 0; j < s2->length; j++) {
            s1->str[i++] = s2->str[j]; // 逐个字符复制
        }
        s1->str[i] = '\0'; // 添加字符串结束标志
        s1->length += s2->length; // 更新长度
    } else {
        printf("连接后的字符串长度超出最大限制！\n");
    }
}

// 比较串
int compareString(const String *s1, const String *s2) {
    int i = 0;
    // 遍历两个字符串，比较字符
    while (i < s1->length && i < s2->length) {
        if (s1->str[i] != s2->str[i]) {
            return s1->str[i] - s2->str[i]; // 返回字符的差值
        }
        i++;
    }
    // 如果s1的长度大于s2，则s1大于s2；如果s2的长度大于s1，则s1小于s2
    return s1->length - s2->length;
}

// 返回主串S中第pos个字符之后的与T相等的字串的位置
int index(String *s, String *t, int pos) {
    // 参数检查
    if (s == NULL || t == NULL || pos < 1) {
        return -1; // 返回-1表示无效输入
    }

    int n = s->length; // 主串的长度
    int m = t->length; // 子串的长度

    // pos为1-based索引，转为0-based索引
    pos--;

    // 从pos位置开始遍历主串
    for (int i = pos; i <= n - m; i++) {
        // 比较当前子串与T
        if (strncmp(s->str + i, t->str, m) == 0) {
            return i; // 返回匹配的起始索引
        }
    }

    return -1; // 如果未找到匹配，则返回-1
}


// 用sub返回串s的第pos个字符起长度为len的字串,求子串
String Substring(String *sub, String s, int pos, int len){
    if (pos < 1 || pos > s.length || len < 0 || (pos + len - 1) > s.length) {
        sub->length = 0;
        sub->str[0] = '\0'; // 设为空字符串
        return *sub; // 返回空子串
    }
    for(int i = 1; i <= len; i++){
        sub->str[i] = s.str[pos + i - 1];
    }

    // 添加字符串结束符
    sub->str[len] = '\0';
    sub->length = len; // 更新子串的长度

    return *sub; // 返回子串
}

int main() {
    String str1, str2;

    // 初始化串
    initString(&str1);
    initString(&str2);

    // 输入串
    inputString(&str1);
    inputString(&str2);

    // 输出串
    outputString(&str1);
    outputString(&str2);

    // 连接串
    concatString(&str1, &str2);
    printf("连接后的字符串为：%s\n", str1.str);

    // 比较串
    int cmpResult = compareString(&str1, &str2);
    if (cmpResult == 0) {
        printf("两个字符串相等。\n");
    } else if (cmpResult < 0) {
        printf("第一个字符串小于第二个字符串。\n");
    } else {
        printf("第一个字符串大于第二个字符串。\n");
    }

    // 示例字符串查找
    String s = {"hello world", 11};
    String t = {"hello", 5};
    int pos = 1; // 从第8个字符开始查找

    int result = index(&s, &t, pos);

    if (result != -1) {
        printf("Substring found at position: %d\n", result + 1); // 输出1-based索引
    } else {
        printf("Substring not found.\n");
    }


    String s1, sub;
    initString(&s1);
    initString(&sub);
    strcpy(s1.str, "Hello, World!"); // 初始化字符串
    s.length = strlen(s1.str); // 计算长度

    int pos1 = 2; // 子串起始位置
    int len = 5; // 子串长度

    Substring(&sub, s1, pos1, len); // 获取子串

    printf("子串: %s\n", sub.str); // 输出子串
    printf("子串长度: %d\n", sub.length); // 输出子串长度


    return 0;
}
