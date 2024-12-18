#include <stdio.h>
#include <stdlib.h>

#define INFINITY 95533	// 最大值
#define MAX_VERTEX_NUM 20	//最大顶点个数
#define VRType int		//顶点关系类型，对无权图，用1或0表示相邻否；对带权图，则为权值类型
#define InfoType int	// 弧类型
#define VErtexType int	//图顶点类型

typedef enum {DG,DN,UDG,UDN}GraphKind;	//图的种类（有向图，有向网，无向图，无向网）

typedef struct ArcCell{
    VRType adj;    //顶点关系类型,对无权图用1或0表示相邻否,对带权图，则为权值类型
    InfoType* info;  //该弧相关信息的指针
}ArcCell, AdjMatrix[MAX_VERTEX_NUM][MAX_VERTEX_NUM];

typedef struct {
    VErtexType vexs[MAX_VERTEX_NUM];	// 顶点向量
    AdjMatrix arcs;		// 邻接矩阵
    int vexnum, arcnum;		// 图的当前顶点数和弧数
    GraphKind	kind;		// 图的种类标志
}MGraph;


//确定某个顶点在图G中的位置
int LocateVex(MGraph *g, VRType point){
    for(int i = 0; i < g->vexnum; i++){
        if(g->vexs[i] == point){
            return i;
        }
    }
}


// 采用数组（邻接矩阵），构造无向图
void CreatUDG(MGraph *g){
    VRType origin, terminus; 	//边的起点,终点
    printf("输入图的顶点数 弧数");
    scanf("%d %d", &(g->vexnum), &(g->arcnum));

    // 存储顶点值
    for(int i = 0; i < g->vexnum; i++){
        printf("输入顶点值");
        scanf("%d", &(g->vexs[i]));
    }

    // 初始化邻接矩阵
    for(int i = 0; i < g->vexnum; i++){
        for(int j = 0; j < g->vexnum; j++){
            g->arcs[i][j].adj = INFINITY;
            g->arcs[i][j].info = NULL;
        }
    }

    // 存入图到邻接矩阵
    for (int k = 0; k < g->arcnum; k++){
        printf("输入一条边的两端:");
        scanf("%d %d", &origin, &terminus);
        //利用LocateVex函数确定起点(origin)及终点(terminus)在G中位置
        int i = LocateVex(g, origin);
        int j = LocateVex(g, terminus);

    }
}















































