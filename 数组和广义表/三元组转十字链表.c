#include<stdio.h>
#include<stdlib.h>

typedef struct OLNode{
    int i, j, e; //矩阵三元组i代表行 j代表列 e代表当前位置的数据
    struct OLNode* right, * down; //指针域 右指针 下指针
}OLNode, * OLink;

typedef struct{
    OLink* rhead, * chead; //行和列链表头指针
    int mu, nu, tu;  //矩阵的行数,列数和非零元的个数
}CrossList;

void CreateMatrix_OL(CrossList* M);

void display(CrossList M);

int main(){
    CrossList M;
    M.rhead = NULL;
    M.chead = NULL;
    CreateMatrix_OL(&M);
    printf("输出矩阵M:\n");
    display(M);
    return 0;
}


void CreateMatrix_OL(CrossList* M)
{
    int m, n, t;
    int num = 0;
    int i, j, e;
    OLNode* p = NULL, * q = NULL;
    printf("输入矩阵的行数、列数和非0元素个数：");
    scanf("%d%d%d", &m, &n, &t);
    (*M).mu = m;
    (*M).nu = n;
    (*M).tu = t;
    if (!((*M).rhead = (OLink*)malloc((m + 1) * sizeof(OLink))) || !((*M).chead = (OLink*)malloc((n + 1) * sizeof(OLink))))
    {
        printf("初始化矩阵失败");
        exit(0);
    }

    for (i = 0; i <= m; i++)
    {
        (*M).rhead[i] = NULL;
    }
    for (j = 0; j <= n; j++)
    {
        (*M).chead[j] = NULL;
    }
    while (num < t) {
        scanf("%d%d%d", &i, &j, &e);
        num++;
        if (!(p = (OLNode*)malloc(sizeof(OLNode))))
        {
            printf("初始化三元组失败");
            exit(0);
        }
        p->i = i;
        p->j = j;
        p->e = e;
        //链接到行的指定位置
        //如果第 i 行没有非 0 元素，或者第 i 行首个非 0 元素位于当前元素的右侧，直接将该元素放置到第 i 行的开头
        if (NULL == (*M).rhead[i] || (*M).rhead[i]->j > j)
        {
            p->right = (*M).rhead[i];
            (*M).rhead[i] = p;
        }
        else
        {
            //找到当前元素的位置
            for (q = (*M).rhead[i]; (q->right) && q->right->j < j; q = q->right);
            //将新非 0 元素插入 q 之后
            p->right = q->right;
            q->right = p;
        }
        //链接到列的指定位置
        //如果第 j 列没有非 0 元素，或者第 j 列首个非 0 元素位于当前元素的下方，直接将该元素放置到第 j 列的开头
        if (NULL == (*M).chead[j] || (*M).chead[j]->i > i)
        {
            p->down = (*M).chead[j];
            (*M).chead[j] = p;
        }
        else
        {
            //找到当前元素要插入的位置
            for (q = (*M).chead[j]; (q->down) && q->down->i < i; q = q->down);
            //将当前元素插入到 q 指针下方
            p->down = q->down;
            q->down = p;
        }
    }
}
void display(CrossList M) {
    int i,j;
    //一行一行的输出
    for (i = 1; i <= M.mu; i++) {
        //如果当前行没有非 0 元素，直接输出 0
        if (NULL == M.rhead[i]) {
            for (j = 1; j <= M.nu; j++) {
                printf("0 ");
            }
            putchar('\n');
        }
        else
        {
            int n = 1;
            OLink p = M.rhead[i];
            //依次输出每一列的元素
            while (n <= M.nu) {
                if (!p || (n < p->j) ) {
                    printf("0 ");
                }
                else
                {
                    printf("%d ", p->e);
                    p = p->right;
                }
                n++;
            }
            putchar('\n');
        }
    }
}
