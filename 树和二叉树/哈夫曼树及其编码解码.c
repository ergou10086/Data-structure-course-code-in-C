#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAXBIT      100
#define MAXVALUE    10000
#define MAXLEAF     30
#define MAXNODE     MAXLEAF * 2 - 1
#define MAXSIZE     5

typedef struct {
    int weight; // 权重
    int parent, lch, rch; // 双亲，左孩子，右孩子
} HTNode, *HuffmanTree;  // HuffmanTree 是 HTNode 类型的指针，指向哈夫曼树的根节点

// 创建哈夫曼树
void CreateHuffmanTree(HuffmanTree *T, int *weights, int n) {
    int m = 2 * n - 1;  // 节点总数
    *T = (HuffmanTree) malloc(m * sizeof(HTNode));

    // 初始化哈夫曼树节点
    for (int i = 0; i < n; i++) {
        (*T)[i].weight = weights[i];
        (*T)[i].parent = -1;
        (*T)[i].lch = -1;
        (*T)[i].rch = -1;
    }
    for (int i = n; i < m; i++) {
        (*T)[i].weight = 0;
        (*T)[i].parent = -1;
        (*T)[i].lch = -1;
        (*T)[i].rch = -1;
    }

    // 构建哈夫曼树
    for (int i = n; i < m; i++) {
        int min1 = -1, min2 = -1;
        // 找到权值最小的两个节点
        for (int j = 0; j < i; j++) {
            if ((*T)[j].parent == -1) {
                if (min1 == -1 || (*T)[j].weight < (*T)[min1].weight) {
                    min2 = min1;
                    min1 = j;
                } else if (min2 == -1 || (*T)[j].weight < (*T)[min2].weight) {
                    min2 = j;
                }
            }
        }

        (*T)[i].weight = (*T)[min1].weight + (*T)[min2].weight;
        (*T)[i].lch = min1;
        (*T)[i].rch = min2;
        (*T)[min1].parent = i;
        (*T)[min2].parent = i;
    }
}

// 生成哈夫曼编码
void GenerateHuffmanCode(HuffmanTree T, char huffCode[MAXLEAF][MAXBIT], int n) {
    char code[MAXBIT];
    code[n - 1] = '\0';  // 初始化空字符

    for (int i = 0; i < n; i++) {
        int start = n - 1;
        int current = i;
        int parent = T[i].parent;

        while (parent != -1) {
            start--;
            if (T[parent].lch == current)
                code[start] = '0';
            else
                code[start] = '1';
            current = parent;
            parent = T[current].parent;
        }
        strcpy(huffCode[i], &code[start]);
    }
}

// 输出哈夫曼编码
void PrintHuffmanCode(char huffCode[MAXLEAF][MAXBIT], char *symbols, int n) {
    for (int i = 0; i < n; i++) {
        printf("Symbol: %c, Huffman Code: %s\n", symbols[i], huffCode[i]);
    }
}

// 哈夫曼编码解码
void DecodeHuffmanCode(HuffmanTree T, char *encodedStr, int n, int *decodedSymbols) {
    int m = 2 * n - 1;
    int index = 0;
    int currentNode = m - 1;  // 从根节点开始
    for (int i = 0; encodedStr[i] != '\0'; i++) {
        if (encodedStr[i] == '0') {
            currentNode = T[currentNode].lch;
        } else if (encodedStr[i] == '1') {
            currentNode = T[currentNode].rch;
        }

        // 如果是叶子节点，则输出符号
        if (currentNode < n) {
            decodedSymbols[index++] = currentNode;
            currentNode = m - 1;  // 回到根节点
        }
    }
}

// 将解码的符号转换为原始字符
void PrintDecodedSymbols(int *decodedSymbols, char *symbols, int index) {
    printf("Decoded string: ");
    for (int i = 0; i < index; i++) {
        printf("%c", symbols[decodedSymbols[i]]);
    }
    printf("\n");
}

int main() {
    // 示例字符串
    char symbols[] = {'a', 'b', 'c', 'd', 'e'};
    int weights[] = {5, 9, 12, 13, 16};
    int n = 5;

    HuffmanTree T;
    CreateHuffmanTree(&T, weights, n);

    // 生成哈夫曼编码
    char huffCode[MAXLEAF][MAXBIT];
    GenerateHuffmanCode(T, huffCode, n);

    // 打印哈夫曼编码
    PrintHuffmanCode(huffCode, symbols, n);

    // 编码后的字符串（例如 "ab" 编码）
    char encodedStr[] = "011011110";  // 这是编码后的二进制字符串

    // 解码
    int decodedSymbols[MAXLEAF];
    DecodeHuffmanCode(T, encodedStr, n, decodedSymbols);
    PrintDecodedSymbols(decodedSymbols, symbols, 2);

    free(T);
    return 0;
}
