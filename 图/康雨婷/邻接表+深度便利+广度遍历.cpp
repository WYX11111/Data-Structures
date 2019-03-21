#include <stdio.h>
#include <stdlib.h>
#include "Queue_Sq.cpp"

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
	fflush(stdin);
	G.arcnum = 0;

	for(i = 0; i < G.vexnum; i++)
	{
		printf("请输入第%d个顶点代表的字符:",i+1);
		scanf("%c",&G.vertics[i].data);
		G.vertics[i].firstarc = NULL;
		fflush(stdin);
	}

	printf("请输入相邻顶点及其权值（空格间隔,如:A B 11.7  以# # #结束）：\n");
	
	scanf("%c %c %f",&v1,&v2,&w);
	fflush(stdin);

	while(v1 != '#')
	{
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

			G.arcnum++;
		}

		scanf("%c %c %f",&v1,&v2,&w);
		fflush(stdin);
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

void DFS(ALGraph G, int i, int *visited)
{
	ArcNode *p;
	
	visited[i] = TRUE;
	printf("%c ",G.vertics[i].data);
	p = G.vertics[i].firstarc;
	
	while(p)
	{
		if( !visited[p->adjvex] )
		{
			DFS(G, p->adjvex, visited);
		}
		p = p->nextarcs;
	}
}

void DFSTraverse(ALGraph G)
{
	int i;
	
	int *visited;
	visited = new int[G.vexnum];

	for( i=0; i < G.vexnum; i++ )
	{
		visited[i] = FALSE;
	}
	
	for( i=0; i < G.vexnum; i++ )
	{
		if( !visited[i] )
		{
			DFS(G, i, visited);
		}
	}
}

void BFSTraverse(ALGraph G)
{ 
	SqQueue Q;
	int v, u, w;
	ArcNode *p;
	int *visited;
	visited = new int[G.vexnum];

	for (v = 0; v < G.vexnum; v++) 
         visited[v] = FALSE;

    InitQueue_Sq(Q);
    for (v=0; v<G.vexnum; ++v)
        if (!visited[v])
		{
            visited[v]  = TRUE;
			
			printf("%c ", G.vertics[v].data);
            EnQueue_Sq(Q, v);

            while (!QueueEmpty_Sq(Q))
			{ 
                DeQueue_Sq(Q, u);

                for (p=G.vertics[u].firstarc; p; p=p->nextarcs )
				{
                    w = p->adjvex;
                    if (!visited[w]) 
					{ 
						visited[w] =TRUE; 
						printf("%c ", G.vertics[w].data);
						EnQueue_Sq(Q,w);
					}                     
                }
			} 
		}   
}


void main()
{
	ALGraph G;
	CreateUDG(G);
//	show_all(G);

	printf("DFS:");
	DFSTraverse(G);
	
	printf("\nBFS:");
	BFSTraverse(G);
}