#include <stdio.h>
#include <stdlib.h>

#define MAX_VERTEX_NUM 20              //�������󶥵���
#define TRUE 1
#define FALSE 0

typedef char VertexType;
typedef float InfoArc;

typedef struct ArcNode
{
	int adjvex;                        //�û���ָ��Ķ���λ��
    struct ArcNode *nextarcs;          //ָ����һ������ָ��
	InfoArc info;                      //�û������Ϣ��ָ��
} ArcNode;

typedef struct VNode                   //����ṹ
{
	VertexType data;                   //������Ϣ
	ArcNode *firstarc;                 //ָ�������ö���ĵ�һ������ָ��
} VNode, AdjList[MAX_VERTEX_NUM];  

typedef struct                         //ͼ�ṹ
{
	AdjList vertics;                   //Ӧ�����ڽӱ�
    int  vexnum, arcnum;               //Ӧ�������������ͻ�����
} ALGraph;                             //ͼ�ṹ

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
  // �����ڽӱ�洢��ʾ����������ͼG��G.kind=UDG����
    int i, j;
	VertexType v1,v2;
	InfoArc w;

	printf("�����붥�����:");
	scanf("%d",&G.vexnum);
	fflush(stdin);
	G.arcnum = 0;

	for(i = 0; i < G.vexnum; i++)
	{
		printf("�������%d�����������ַ�:",i+1);
		scanf("%c",&G.vertics[i].data);
		G.vertics[i].firstarc = NULL;
		fflush(stdin);
	}

	printf("���������ڶ��㼰��Ȩֵ���ո���,��:A B 11.7  ��# # #��������\n");
	
	scanf("%c %c %f",&v1,&v2,&w);
	fflush(stdin);

	while(v1 != '#')
	{
		i = locatevex(G,v1);
		j = locatevex(G,v2);
		if (i == G.vexnum || j == G.vexnum)
			printf("���㲻����\n");
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

void main()
{
	ALGraph G;
	CreateUDG(G);
//	show_all(G);
	DFSTraverse(G);
}