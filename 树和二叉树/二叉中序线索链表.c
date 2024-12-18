#include <stdio.h>
#include <stdlib.h>

typedef char dataType;
typedef struct node
{
    dataType data; //根节点的值
    struct node *lchild; //左孩子
    struct node *rchild; //右孩子
    int ltag; //左标记，“ltag=0”表示当前节点有左孩子，“ltag=1”表示当前节点没有左孩子
    int rtag; //右标记，“rtag=0”表示当前节点有右孩子，“rtag=1”表示当前节点没有右孩子
}BiTree;

BiTree *creat() //二叉树的创建及初始化(初始化左右标记为0)
{
    dataType value;
    BiTree *t;

    scanf("%c",&value);

    if(value=='#')
    {
        t=NULL;
    }
    else
    {
        t=(BiTree *)malloc(sizeof(BiTree));
        t->data=value;
        t->ltag=0;//初始化左标记为0
        t->rtag=0;//初始化右标记为0
        t->lchild=creat();
        t->rchild=creat();
    }
    return t;
}

//BiTree *pre=NULL; //1.定义全局变量pre
void InThreaded(BiTree *p)
{
    static BiTree *pre=NULL;//2.定义静态变量
    if(p)
    {
        InThreaded(p->lchild);

        if(!p->lchild)
        {
            p->ltag=1;
            p->lchild=pre;
        }

        if(pre&&!pre->rchild)
        {
            pre->rtag=1;
            pre->rchild=p;
        }
        pre=p;

        InThreaded(p->rchild);
    }
}

BiTree *Next(BiTree *t) //已知节点t找t的"后继"结点位置
{
    if(t->rtag==1) //右标志为1，可以直接得到"后继"结点
    {
        t=t->rchild;
    }
    else /*右标志为0，不能直接的到"后继"结点，
	        则需要找到右子树最左下角的节点*/
    {
        t=t->rchild;
        while(t->ltag==0)
        {
            t=t->lchild;
        } //while
    }//else
    return t;
}

BiTree *Prior(BiTree *t)//已知节点t找t的"前驱"结点位置
{
    if(t->ltag==1)//左标志为1，可以直接找到"前驱"结点的位置
    {
        t=t->lchild;
    }
    else /*右标志为0，不能直接的到"前驱"结点，
	       则需要找到左子树最右下角的节点*/
    {
        t=t->lchild;
        while(t->rtag==0)
        {
            t=t->rchild;
        } //while
    } //else

    return t;
}

void InorderTraverse(BiTree *t){//利用线索实现中序遍历

    if(!t) { return; }

    while(t->ltag==0){
        //查找第一个节点
        // 因为二叉树的创建creat是以先序遍历序列创建，所以t所指向的第一个结点并不是中序遍历所要访问的第一个结点
        t=t->lchild;
    }
    printf("%c ",t->data);//访问第一个结
    while(t->rchild){ // 此处以"t的右孩子不为空"为循环条件，是因为，先前设定了最后一个结点的"后继"为空，表示结束
        //根据线索访问后续结点
        t=Next(t);
        printf("%c ",t->data);
    }
}

int main()
{
    BiTree *root;

    printf("Input:");
    root=creat();
    printf("\n");

    printf("Threading Binary Tree!\n");
    InThreaded(root);
    printf("\n");

    printf("Inorder traverse:");
    InorderTraverse(root);
    printf("\n");


    return 0;
}
