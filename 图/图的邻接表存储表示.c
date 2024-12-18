#include <stdio.h>
#include <stdlib.h>

#define MAX_VERTEX_NUM 20	//最大顶点个数
#define VRType int		//顶点关系类型，对无权图，用1或0表示相邻否；对带权图，则为权值类型
#define InfoType int	// 弧类型
#define VErtexType int	//图顶点类型

// 邻接表链表指针
typedef struct ArcNode{
    int adjvex;   // 该弧所指向的顶点的位置
    struct ArcNode* nextarc;   // 指向下一条弧的指针
    InfoType *info;   // 该弧相关信息的指针
}ArcNode;

// 表头数组
typedef struct VNode{
    VErtexType data;   // 顶点信息
    ArcNode *firstarc;   // 指向该顶点的第一条弧
}VNode, AdjList[MAX_VERTEX_NUM];

// 邻接表本体结构体
typedef struct {
    AdjList vertices;
    int vexnum, arcnum; // 图的当前顶点数和弧数
    int kind; // 图的种类标志
};