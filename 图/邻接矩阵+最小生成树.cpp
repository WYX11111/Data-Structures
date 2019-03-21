#include <stdio.h>
#include <stdlib.h>
#include "Queue_Sq.cpp"

#define INFINITY  1107       //���ֵ��
#define MAX_VERTEX_NUM      20  //�������󶥵���

typedef float VRType;
typedef char VertexType;

typedef struct			//����С�����������ø�������Ľṹ�嶨��
{
	VertexType adjvex;
	VRType lowcost;
}closedge[MAX_VERTEX_NUM];

typedef struct ArcCell                             //�����ߣ����Ķ���
{	
	VRType adj;                                    //������ϵ����Ȩͼȡ1��0����ȨͼȡȨֵ����
	//InfoType *info;                              //�û������Ϣ��ָ��
} ArcCell, AdjMatrix [MAX_VERTEX_NUM][MAX_VERTEX_NUM];

typedef struct                                     //ͼ�Ķ��壺����������ֱ�洢�������ڽӾ���
{    
	VertexType vexs [MAX_VERTEX_NUM];              //�������������
	int visited[MAX_VERTEX_NUM];                   //������־
    AdjMatrix arcs;                                //�ڽӾ���
    int vernum, arcnum;                            //���������������ߣ�����
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

	printf("�����붥�����:");
	scanf("%d",&G.vernum);
	fflush(stdin);
	G.arcnum = 0;

	for(i = 0; i < G.vernum; i++)
	{
		printf("�������%d�����������ַ�:",i+1);
		scanf("%c",&G.vexs[i]);
		fflush(stdin);
	}

	for(i = 0; i < G.vernum; i++)			        //��ʼ���ڽӾ���
		for(j = 0; j<G.vernum; j++)
			G.arcs[i][j].adj = INFINITY;

	printf("���������ڶ��㼰��Ȩֵ���ո���,��:A B 11.7  ��# # #��������\n");
	
	scanf("%c %c %f",&v1,&v2,&w);
	fflush(stdin);

	while(v1 != '#')
	{
		i = locatevex(G,v1);
		j = locatevex(G,v2);
		if (i == G.vernum || j == G.vernum)
			printf("���㲻����\n");
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
    SqQueue Q;                                               // ����ѭ������Q
      
	set_visited(G);
	
	InitQueue_Sq(Q,G.vernum);          

	for (v = 0; v < G.vernum; v++)
		if (!G.visited[v]) 
		{               
			G.visited[v] = 1;
			
			printf("%c ",G.vexs[v]);                           // ����ͼ�е�v������
            
			EnQueue_Sq(Q, v);                                 // v�����
            while (!QueueEmpty_Sq(Q))  
			{
				DeQueue_Sq(Q, u);                             // ��ͷԪ�س��Ӳ���Ϊu
				for ( w=0;  w<G.vernum;  w++ )
					if ( G.arcs[u][w].adj && ! G.visited[w] ) 
					{
						G.visited[w] = 1;
						printf("%c ",G.vexs[w]);               // ����ͼ�е�w������
						EnQueue_Sq(Q, w);                     // ��ǰ���ʵĶ���w�����Q
					}
			}
		}
}

int minimum(closedge hp,Mgraph G)		//�ҵ��ܵ�Ȩֵ��С�ıߣ��������ڸ��������е����
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

void MiniSpanTree(Mgraph G,VertexType u)	//������ͼ���ҵ���С����������������С�Ĺܵ�����·��
{
	int i,j,k;
	closedge help;

	k=locatevex(G,u);
	
//	printf ("�Ӿ�����A������\n");
	
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
//		printf("�Ӿ�����%c��������%c��·�ߣ�",help[k].adjvex,G.vexs[k]);
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
	printf("���·����\n");
	MiniSpanTree(G,G.vexs[0]);
}