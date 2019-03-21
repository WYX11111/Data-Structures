#include<stdio.h>
#include<stdlib.h>
#define OK 1
#define MAX_CITIZENS_NUM 30	//最多居民区，即无向图中最大顶点数
#define INFINITY 99.0
typedef int Status;
typedef char vertextype;
typedef float vrtype;

typedef struct			//求最小生成树中所用辅助数组的结构体定义
{
	vertextype adjvex;
	vrtype lowcost;
}closedge[ MAX_CITIZENS_NUM];

typedef struct arccell			//邻接矩阵的结构体类型定义
{
	vrtype adj;
}arccell,adjmatrix[MAX_CITIZENS_NUM][MAX_CITIZENS_NUM];

typedef struct			//图的结构体类型定义
{
	vertextype vexs[MAX_CITIZENS_NUM];
	adjmatrix  arcs;
	int vexnum,arcnum;
}graph;

int locatevex(graph G,char v) //找到输入的顶点在G.vexs[]中的位置，返回编号
{
	int i;
	for (i=0;i<G.vexnum;i++)
		if(v==G.vexs[i])     break;
	if (i>=G.vexnum)
		return -1;
	return i;
}

Status createg(graph* G)		//构建无向图
{
	int m,i,j,k;
	float w;
	char v1,v2;
	printf("请输入居民区总数，以及每个点可以铺设的管道数目:");
	scanf("%d %d",&G->vexnum,&G->arcnum);
	getchar();
	for(m=0;m<G->vexnum;m++)
	          {
				printf("请输入第%d个居民区代表的字符:",m+1);
				scanf("%c",&G->vexs[m]);
				getchar();
	          }
	         
	for(i=0;i<G->vexnum;i++)			//初始化邻接矩阵
		for(j=0;j<G->vexnum;j++)
			G->arcs[i][j].adj=INFINITY;		
	printf("请输入各条管道所依附的两个居民区及其权值（空格间隔）：\n");
	for(k=0;k<G->arcnum;k++)
	       {
				scanf("%c %c %f",&v1,&v2,&w);
				getchar();
				i=locatevex(*G,v1);
				j=locatevex(*G,v2);
				G->arcs[i][j].adj=G->arcs[j][i].adj=w;
	      }
	return OK;
}

Status printfgraph(graph G)	//在屏幕上输出邻接矩阵存储的无向图
{
	int i,j;
	printf("**************************************** \n");
	printf("输出的邻接矩阵为：\n"); 
	printf("---99.0 代表无穷大 ---\n");
	for(i=0;i<G.vexnum;i++)
   		 printf("%7c",G.vexs[i]);
	printf("\n");
	for(i=0;i<G.vexnum;i++)
	          {
				printf("%c   ",G.vexs[i]);	//输出居民区代表的字符
				for(j=0;j<G.vexnum;j++)
				printf("%-7.1f",G.arcs[i][j].adj);
 				printf("\n");
	          }
	return OK;
}

static int minimum(closedge hp,graph  G)		//找到管道权值最小的边，返回其在辅助数组中的序号
{
	float min;
	int i=0,j,k;
	while(!hp[i].lowcost)
		i++;
	min=hp[i].lowcost;
	k=i;
	for(j=i+1;j<G.vexnum;j++)
	           {
					if(hp[j].lowcost>0&&hp[j].lowcost<min)
						{
							min=hp[j].lowcost;
							k=j;
       					}
               }
	return k;
}

void MiniSpanTree(graph  G,vertextype u)	//在无向图中找到最小生成树，即代价最小的管道铺设路线
{
	int i,j,k;
	closedge help;
	k=locatevex(G,u);
	printf ("从居民区A出发：\n");
	for(j=0;j<G.vexnum;j++)
	        {
				if(j!=k)
    				{
						help[j].adjvex=u;
						help[j].lowcost=G.arcs[k][j].adj;
      				}
          		help[k].lowcost=0.0;
	         }
	for(i=1;i<G.vexnum;i++)
 		{
			k=minimum(help,G);
			printf("从居民区%c到居民区%c的路线：",help[k].adjvex,G.vexs[k]);
			printf("(%c,%c)\n",help[k].adjvex,G.vexs[k]);
			help[k].lowcost=0.0;
			for(j=0;j<G.vexnum;j++)
   				if(G.arcs[k][j].adj<help[j].lowcost)
		      		{	
			           help[j].adjvex=G.vexs[k];
			           help[j].lowcost=G.arcs[k][j].adj;
              		}
  	    }
	printf("\n");
}

int main()
{	
	graph G;
	printf("			    管道铺设施工的最佳方案						"); 
	printf("********************************************  \n");
	printf("         欢迎您使用本程序，本程序可以帮助您    \n"); 
	printf("            		选择管道铺设施工的最佳方案		\n");
	printf("********************************************  \n");
	createg(&G);
	printfgraph(G);
	MiniSpanTree(G,G.vexs[0]);
	return 0; 
}
