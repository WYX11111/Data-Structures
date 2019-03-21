#include <stdio.h>
#include <stdlib.h>

#define INFINITY  INT_MAX       //最大值∞
#define MAX_VERTEX_NUM      20  //假设的最大顶点数

typedef int VRType;
typedef char VertexType

typedef enum 
{
	DG, DN, AG,AN 
} GraphKind;                                       //有 向/无向图，有向/无向网

typedef struct ArcCell                             //弧（边）结点的定义
{	
	VRType adj;                                    //顶点间关系，无权图取1或0；有权图取权值类型
	InfoType *info;                                //该弧相关信息的指针
} ArcCell, AdjMatrix [MAX_VERTEX_NUM][MAX_VERTEX_NUM];

typedef struct{                                    //图的定义：用两个数组分别存储顶点表和邻接矩阵
{    
	VertexType vexs [MAX_VERTEX_NUM];              //描述顶点的数组
    AdjMatrix arcs;                                //邻接矩阵
    int vernum, arcnum;                            //顶点总数，弧（边）总数
    GraphKind kind;                                //图的种类标志
} Mgraph;