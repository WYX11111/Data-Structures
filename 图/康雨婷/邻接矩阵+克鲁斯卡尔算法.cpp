#include <stdio.h>
#include <stdlib.h>

#define MAX_VERTEX_NUM 20

typedef int VRType;
typedef char VertexType;

typedef struct ArcCell
{	
	VRType adj;
} ArcCell, AdjMatrix [MAX_VERTEX_NUM][MAX_VERTEX_NUM];

typedef struct
{    
	VertexType vexs [MAX_VERTEX_NUM];
    AdjMatrix arcs;
    int vexnum, arcnum;
} Mgraph;

int locatevex(Mgraph &G, VertexType v)
{
	int i;
	for (i = 0; i < G.vexnum; i++)
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

	printf("�����붥�����:");
	scanf("%d",&G.vexnum);

	printf("������ߵĸ���:");
	scanf("%d",&G.arcnum);
	fflush(stdin);

	for(i = 0; i < G.vexnum; i++)
	{
		printf("�������%d�����������ַ�:",i+1);
		scanf("%c",&G.vexs[i]);
		fflush(stdin);
	}

	for(i = 0; i < G.vexnum; i++)			        //��ʼ���ڽӾ���
		for(j = 0; j<G.vexnum; j++)
			G.arcs[i][j].adj = 0;

	printf("���������ڶ���\n");

	for(int k = 0; k < G.arcnum; k++)
	{
		scanf("%c %c",&v1,&v2);
		fflush(stdin);

		i = locatevex(G,v1);
		j = locatevex(G,v2);
		if (i == G.vexnum || j == G.vexnum)
			printf("���㲻����\n");
		else
			G.arcs[i][j].adj = 1;
	}
}

void main()
{
	Mgraph G;
	create(G);
	int num = 0,i;
	char v1;
	printf("���붥��");
	scanf("%c",&v1);
	int k = locatevex(G,v1);
	
	for(i = 0; i < G.vexnum; i++)
	{
		if(G.arcs[i][k].adj != 0)
		{
			num++;
		}
	}

	for(i = 0; i < G.vexnum; i++)
	{
		if(G.arcs[k][i].adj != 0)
		{
			num++;
		}
	}

	printf("%d",num);
}