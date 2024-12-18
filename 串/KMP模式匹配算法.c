#include <stdio.h>
#include <string.h>
#include <stdlib.h>
// s为主串，p为子串

// 朴素的模式匹配
int BFMatch(char *s, char *p){
    int i = 0, j;
    while(i < strlen(s)){
        j = 0;
        while(s[i] == p[i] && j < strlen(p)){
            // 成功匹配，继续向后匹配字符
            i++, j++;
        }
        // 到头了返回结果
        if(j == strlen(p)){
            return i - strlen(p);
        }
        // 失配的时候回溯到开始匹配的位置的下一个位置继续匹配
        i = i - j + 1;
    }
    return -1;
}


int KMPMatch_pr(char *s, char *p){
    const int N = 1000010;
    // 模式串P，主串S
    int nxt[N], ls, lp;

    ls = strlen(s+1), lp = strlen(p+1);

    nxt[1] = 0;
    for(int i = 2, j = 0; i <= lp; i++){
        while(j && p[i] != p[j + 1]){ j = nxt[j]; }
        if(p[i] == p[j + 1]) j++;
        nxt[i] = j;
    }

    for(int i = 1, j = 0; i <= ls; i ++){
        while(j && s[i] != p[j + 1]) j = nxt[j];
        if(s[i] == p[j+1]) j++;
        if(j == lp) return ("%d\n", i-lp+1);
    }
    return 0;
}

// 计算模式串 p 的 next 数组
void Get_Next(char *p, int nxt[]) {
    int i = 1, j = 0; // i 为当前 p 的位置，j 为前缀的长度
    int lp = strlen(p);
    nxt[0] = 0; // next[0] 没有前缀，所以为 0

    while (i < lp) {
        if (j == 0 || p[i] == p[j]) {
            i++;
            j++;
            nxt[i] = j; // 记录模式串中第 i 个字符的前缀长度
        } else {
            j = nxt[j]; // 更新 j
        }
    }
}

// KMP 算法匹配主串 s 和模式串 p，从 pos 开始匹配
int KMP(char *s, char *p, int pos) {
    int i = pos, j = 0; // i 为当前 s 的位置，j 为当前 p 的位置
    int ls = strlen(s), lp = strlen(p);
    int nxt[10000];
    Get_Next(p, nxt);

    while (i < ls && j < lp) {
        if (j == -1 || s[i] == p[j]) {
            i++;
            j++;
        } else {
            j = nxt[j]; // 失败时跳到模式串中的下一个位置
        }
    }

    // 如果匹配成功
    if (j == lp) return i - lp; // 返回匹配开始的位置
    else return -1; // 未找到匹配
}

int main(void) {
    int res;
    char s[] = "ccabaabcdshjdsjhdshj"; // 主串
    char p[] = "abaabc"; // 模式串
    int nxt[10000];
    Get_Next(p, nxt);

    res = KMP(s, p, 0);
    for (int i = 0; i < strlen(p); i++) {
        printf("%d ", nxt[i]);
    }
    printf("\nResult: %d\n", res);
    return 0;
}
