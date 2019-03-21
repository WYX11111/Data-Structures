#include <stdio.h>
#include <stdlib.h>
#include "Queue_Sq.cpp"

#define INFINITY  1107       //最大值∞
#define MAX_VERTEX_NUM      20  //假设的最大顶点数

typedef float VRType;
typedef char VertexType;

typedef struct			//求最小生成树中所用辅助数组的结构体定义
{
	VertexType adjvex;
	VRType lowcost;
}closedge[MAX_VERTEX_NUM];

typedef struct ArcCell                             //弧（边）结点的定义
{	
	VRType adj;                                    //顶点间关系，无权图取1或0；有权图取权值类型
	//InfoType *info;                              //该弧相关信息的指针
} ArcCell, AdjMatrix [MAX_VERTEX_NUM][MAX_VERTEX_NUM];

typedef struct                                     //图的定义：用两个数组分别存储顶点表和邻接矩阵
{    
	VertexType vexs [MAX_VERTEX_NUM];              //描述顶点的数组
	int visited[MAX_VERTEX_NUM];                   //遍历标志
    AdjMatrix arcs;                                //邻接矩阵
    int vernum, arcnum;                            //顶点总数，弧（边）总数
} Mgraph;

int locatevex(Mgraph &G, VertexType v)
{
	int i;
	for (i = 0; i < G.vernum; i++)
	{
		if(v == G.vexs[i])
			break;
	}
	return i;
}

void create(Mgraph &G)
{
	int i,j;
	char v1,v2;
	float w;

	printf("请输入顶点个数:");
	scanf("%d",&G.vernum);
	fflush(stdin);
	G.arcnum = 0;

	for(i = 0; i < G.vernum; i++)
	{
		printf("请输入第%d个顶点代表的字符:",i+1);
		scanf("%c",&G.vexs[i]);
		fflush(stdin);
	}

	for(i = 0; i < G.vernum; i++)			        //初始化邻接矩阵
		for(j = 0; j<G.vernum; j++)
			G.arcs[i][j].adj = INFINITY;

	printf("请输入相邻顶点及其权值（空格间隔,如:A B 11.7  以# # #结束）：\n");
	
	scanf("%c %c %f",&v1,&v2,&w);
	fflush(stdin);

	while(v1 != '#')
	{
		i = locatevex(G,v1);
		j = locatevex(G,v2);
		if (i == G.vernum || j == G.vernum)
			printf("顶点不存在\n");
		else
		{
			G.arcs[i][j].adj = w;
			G.arcs[j][i].adj = w;
			G.arcnum++;
		}

		scanf("%c %c %f",&v1,&v2,&w);
		fflush(stdin);
	}
}

void print_all(Mgraph &G)
{
	int i,j;
	for (i = 0; i < G.vernum; i++)
		printf("%7c",G.vexs[i]);

	for (i = 0; i < G.vernum; i++)
	{
		printf("\n%c   ",G.vexs[i]);

		for (j = 0; j < G.vernum; j++)
		{
			if(G.arcs[i][j].adj == INFINITY)
				printf("***    ");
			else printf("%-7.1f",G.arcs[i][j].adj);
		}
	}
}

void set_visited(Mgraph &G)
{
	for(int i = 0; i < G.vernum; i++)
		G.visited[i] = 0;
}

void DFS(Mgraph &G, int n, int v) 
{
	int j;
	G.visited[v]=1;
	printf("%c ",G.vexs[v]);
	for( j = 0; j < n; j++) 
       if (G.arcs[v][j].adj != INFINITY && G.visited[j] == 0)  
		   DFS(G, n, j);
}

void BFSTraverse(Mgraph G) 
{
	int v,w,u;
    SqQueue Q;                                               // 附设循环队列Q
      
	set_visited(G);
	
	InitQueue_Sq(Q,G.vernum);          

	for (v = 0; v < G.vernum; v++)
		if (!G.visited[v]) 
		{               
			G.visited[v] = 1;
			
			printf("%c ",G.vexs[v]);                           // 访问图中第v个顶点
            
			EnQueue_Sq(Q, v);                                 // v入队列
            while (!QueueEmpty_Sq(Q))  
			{
				DeQueue_Sq(Q, u);                             // 队头元素出队并置为u
				for ( w=0;  w<G.vernum;  w++ )
					if ( G.arcs[u][w].adj && ! G.visited[w] ) 
					{
						G.visited[w] = 1;
						printf("%c ",G.vexs[w]);               // 访问图中第w个顶点
						EnQueue_Sq(Q, w);                     // 当前访问的顶点w入队列Q
					}
			}
		}
}

int minimum(closedge hp,Mgraph G)		//找到管道权值最小的边，返回其在辅助数组中的序号
{
	float min;
	int i = 0, j, k;

	while(!hp[i].lowcost)
		i++;
	
	min = hp[i].lowcost;
	k = i;

	for(j = i+1; j < G.vernum; j++)
	{
		if(hp[j].lowcost > 0 && hp[j].lowcost < min)
		{
			min = hp[j].lowcost;
			k = j;
		}
	}
	return k;
}

void MiniSpanTree(Mgraph G,VertexType u)	//在无向图中找到最小生成树，即代价最小的管道铺设路线
{
	int i,j,k;
	closedge help;

	k=locatevex(G,u);
	
//	printf ("从居民区A出发：\n");
	
	for(j=0;j<G.vernum;j++)
	{
		if(j!=k)
   		{
			help[j].adjvex=u;
			help[j].lowcost=G.arcs[k][j].adj;
      	}
   		help[k].lowcost=0.0;
	}
	
	for(i=1;i<G.vernum;i++)
 	{
		k=minimum(help,G);
//		printf("从居民区%c到居民区%c的路线：",help[k].adjvex,G.vexs[k]);
		printf("(%c,%c)\n",help[k].adjvex,G.vexs[k]);
		help[k].lowcost=0.0;
		for(j=0;j<G.vernum;j++)
   			if(G.arcs[k][j].adj<help[j].lowcost)
			{	
				help[j].adjvex=G.vexs[k];
				help[j].lowcost=G.arcs[k][j].adj;
			}
	}
	printf("\n");
}
void main()
{
	Mgraph G;
	create(G);
	set_visited(G);
	DFS(G, G.vernum, 1);
	printf("\n");
	set_visited(G);
	BFSTraverse(G);
	printf("\n");
	print_all(G);
	printf("最短路径：\n");
	MiniSpanTree(G,G.vexs[0]);
}