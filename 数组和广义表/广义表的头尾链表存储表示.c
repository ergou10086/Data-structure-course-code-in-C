#include <stdio.h>
#include <stdlib.h>

// 定义广义表的节点
typedef struct GLNode {
    int tag;               // 标志域，标记是否是原子元素：0 - 原子元素, 1 - 子表
    union {
        char atom;   // atom是原子结点的值域
        struct GLNode* hp;  // 当为子表时，hp指向表头
    } data;
    struct GLNode* tp;    // tp指向表尾
} GLNode, *Glist;

// 创建原子元素的节点
Glist CreateAtom(int atom) {
    Glist newNode = (Glist)malloc(sizeof(GLNode));
    newNode->tag = 0;  // 原子元素
    newNode->data.atom = atom;
    newNode->tp = NULL;
    return newNode;
}

// 创建子表的节点
Glist CreateSublist(Glist sublist) {
    Glist newNode = (Glist)malloc(sizeof(GLNode));
    newNode->tag = 1;  // 子表
    newNode->data.hp = sublist;
    newNode->tp = NULL;
    return newNode;
}

// 打印广义表的元素
void PrintGL(Glist gl) {
    if (!gl) return;
    if (gl->tag == 0) {
        // 打印原子元素
        printf("%c ", gl->data.atom);
    } else {
        // 打印子表，递归调用
        printf("(");
        PrintGL(gl->data.hp);
        printf(") ");
    }
    PrintGL(gl->tp);  // 打印尾部
}

// 计算广义表的深度
int GetDepth(Glist gl) {
    if (!gl) return 0;  // 空广义表的深度为0
    if (gl->tag == 0) {
        // 原子元素的深度为0
        return 0;
    } else {
        // 递归计算子表的深度，并加1
        int sublist_depth = GetDepth(gl->data.hp);
        int tail_depth = GetDepth(gl->tp);
        return (sublist_depth > tail_depth? sublist_depth : tail_depth) + 1;
    }
}

int main() {
    // 构建一个广义表：(a (b c) (d (e f)))
    Glist gl1 = CreateAtom('a');
    Glist gl2 = CreateAtom('b');
    Glist gl3 = CreateAtom('c');
    Glist gl4 = CreateAtom('d');
    Glist gl5 = CreateAtom('e');
    Glist gl6 = CreateAtom('f');

    Glist sublist1 = CreateSublist(gl2);
    Glist sublist2 = CreateSublist(gl4);
    Glist sublist3 = CreateSublist(gl5);
    Glist sublist4 = CreateSublist(gl6);

    gl1->tp = CreateSublist(sublist1);  // a -> (b c)
    sublist1->tp = CreateSublist(sublist2);  // (b c) -> (d (e f))
    sublist2->tp = CreateSublist(sublist3); // (d (e f)) -> (e f)
    sublist3->tp = sublist4; // (e f) -> f

    // 打印广义表
    printf("The generalized list is: ");
    PrintGL(gl1);
    printf("\n");

    // 计算广义表的深度
    int depth = GetDepth(gl1);
    printf("The depth of the generalized list is: %d\n", depth);

    return 0;
}