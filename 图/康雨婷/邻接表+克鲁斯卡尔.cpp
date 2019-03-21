#include <stdio.h>
#include <stdlib.h>

#define MAX_VERTEX_NUM 20              //假设的最大顶点数
#define TRUE 1
#define FALSE 0

typedef char VertexType;
typedef float InfoArc;

typedef struct ArcNode
{
	int adjvex;                        //该弧所指向的顶点位置
    struct ArcNode *nextarcs;          //指向下一条弧的指针
	InfoArc info;                      //该弧相关信息的指针
} ArcNode;

typedef struct VNode                   //顶点结构
{
	VertexType data;                   //顶点信息
	ArcNode *firstarc;                 //指向依附该顶点的第一条弧的指针
} VNode, AdjList[MAX_VERTEX_NUM];  

typedef struct                         //图结构
{
	AdjList vertics;                   //应包含邻接表
    int  vexnum, arcnum;               //应包含顶点总数和弧总数
} ALGraph;                             //图结构


typedef struct
{
	int data;                          //顶点信息
	int set;   
} VEX;

typedef struct 
{    
	int vexs, vexe;                    //边依附的两顶点
    InfoArc score;                      //边的权值
    int flag;                          //标志域
} EDGE;


int locatevex(ALGraph &G, VertexType v)
{
	int i;
	for (i = 0; i < G.vexnum; i++)
	{
		if(v == G.vertics[i].data)
			break;
	}
	return i;
}

void CreateUDG(ALGraph &G) 
{     
  // 采用邻接表存储表示，构造无向图G（G.kind=UDG）。
    int i, j;
	VertexType v1,v2;
	InfoArc w;

	printf("请输入顶点个数:");
	scanf("%d",&G.vexnum);
	
	printf("请输入边的个数:");
	scanf("%d",&G.arcnum);

	fflush(stdin);
	
	for(i = 0; i < G.vexnum; i++)
	{
		printf("请输入第%d个顶点代表的字符:",i+1);
		scanf("%c",&G.vertics[i].data);
		G.vertics[i].firstarc = NULL;
		fflush(stdin);
	}

	printf("请输入相邻顶点及其权值（空格间隔,如:A B 11.7）：\n");

	for(int k = 0; k < G.arcnum; k++)
	{
		scanf("%c %c %f",&v1,&v2,&w);
		fflush(stdin);
		
		i = locatevex(G,v1);
		j = locatevex(G,v2);
		if (i == G.vexnum || j == G.vexnum)
			printf("顶点不存在\n");
		else
		{
			ArcNode *pi = new ArcNode;
			
			pi->adjvex = j;
			pi->nextarcs = G.vertics[i].firstarc;
			G.vertics[i].firstarc = pi;
            pi->info = w;
						
			ArcNode *pj = new ArcNode;                       
			pj->adjvex = i;                           
			pj->nextarcs = G.vertics[j].firstarc;
			G.vertics[j].firstarc = pj;                
			pj->info = w;
		}
	}
}

void show_all(ALGraph G)
{
	int i;
	ArcNode *p;
	for(i = 0; i < G.vexnum; i++)
	{
		printf("\n%c", G.vertics[i].data);
		p = G.vertics[i].firstarc;
		while(p)
		{
			printf("-->");
//			printf("%f",p->info);
			printf("%c", G.vertics[p->adjvex]);
			p = p->nextarcs;
		}
	}
	printf("\n");
}

void main()
{
	ALGraph G;
	CreateUDG(G);
//	show_all(G);
}