#include <stdio.h>
#include <stdlib.h>

#define MAX_VERTEX_NUM   20
#define VRType int		//顶点关系类型，对无权图，用1或0表示相邻否；对带权图，则为权值类型
#define InfoType int	// 弧类型
#define VErtexType int	//图顶点类型

// 弧结点
typedef struct ArcBox {
    int   tailvex, headvex; // 该弧的尾和头顶点的位置
    struct  ArcBox   *hlink,  *tlink;   // 分别指向下一个弧头相同和弧尾相同的弧的指针域
    InfoType *info;   // 该弧相关信息的指针
} ArcBox;

// 表头结点
typedef struct VexNode {
    VErtexType   data;
    ArcBox   *firstin,  *firstout;  // 分别指向该顶点第一条入弧和出弧
} VexNode;

// 十字链表本体
typedef struct {
    VexNode  xlist[MAX_VERTEX_NUM]; // 表头向量
    int   vexnum, arcnum; // 有向图的当前顶点数和弧数
} OLGraph;
