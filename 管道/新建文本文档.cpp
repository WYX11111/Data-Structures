#include<stdio.h>
#include<stdlib.h>
#define OK 1
#define MAX_CITIZENS_NUM 30	//����������������ͼ����󶥵���
#define INFINITY 99.0
typedef int Status;
typedef char vertextype;
typedef float vrtype;

typedef struct			//����С�����������ø�������Ľṹ�嶨��
{
	vertextype adjvex;
	vrtype lowcost;
}closedge[ MAX_CITIZENS_NUM];

typedef struct arccell			//�ڽӾ���Ľṹ�����Ͷ���
{
	vrtype adj;
}arccell,adjmatrix[MAX_CITIZENS_NUM][MAX_CITIZENS_NUM];

typedef struct			//ͼ�Ľṹ�����Ͷ���
{
	vertextype vexs[MAX_CITIZENS_NUM];
	adjmatrix  arcs;
	int vexnum,arcnum;
}graph;

int locatevex(graph G,char v) //�ҵ�����Ķ�����G.vexs[]�е�λ�ã����ر��
{
	int i;
	for (i=0;i<G.vexnum;i++)
		if(v==G.vexs[i])     break;
	if (i>=G.vexnum)
		return -1;
	return i;
}

Status createg(graph* G)		//��������ͼ
{
	int m,i,j,k;
	float w;
	char v1,v2;
	printf("������������������Լ�ÿ�����������Ĺܵ���Ŀ:");
	scanf("%d %d",&G->vexnum,&G->arcnum);
	getchar();
	for(m=0;m<G->vexnum;m++)
	          {
				printf("�������%d��������������ַ�:",m+1);
				scanf("%c",&G->vexs[m]);
				getchar();
	          }
	         
	for(i=0;i<G->vexnum;i++)			//��ʼ���ڽӾ���
		for(j=0;j<G->vexnum;j++)
			G->arcs[i][j].adj=INFINITY;		
	printf("����������ܵ�����������������������Ȩֵ���ո�������\n");
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

Status printfgraph(graph G)	//����Ļ������ڽӾ���洢������ͼ
{
	int i,j;
	printf("**************************************** \n");
	printf("������ڽӾ���Ϊ��\n"); 
	printf("---99.0 ��������� ---\n");
	for(i=0;i<G.vexnum;i++)
   		 printf("%7c",G.vexs[i]);
	printf("\n");
	for(i=0;i<G.vexnum;i++)
	          {
				printf("%c   ",G.vexs[i]);	//���������������ַ�
				for(j=0;j<G.vexnum;j++)
				printf("%-7.1f",G.arcs[i][j].adj);
 				printf("\n");
	          }
	return OK;
}

static int minimum(closedge hp,graph  G)		//�ҵ��ܵ�Ȩֵ��С�ıߣ��������ڸ��������е����
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

void MiniSpanTree(graph  G,vertextype u)	//������ͼ���ҵ���С����������������С�Ĺܵ�����·��
{
	int i,j,k;
	closedge help;
	k=locatevex(G,u);
	printf ("�Ӿ�����A������\n");
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
			printf("�Ӿ�����%c��������%c��·�ߣ�",help[k].adjvex,G.vexs[k]);
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
	printf("			    �ܵ�����ʩ������ѷ���						"); 
	printf("********************************************  \n");
	printf("         ��ӭ��ʹ�ñ����򣬱�������԰�����    \n"); 
	printf("            		ѡ��ܵ�����ʩ������ѷ���		\n");
	printf("********************************************  \n");
	createg(&G);
	printfgraph(G);
	MiniSpanTree(G,G.vexs[0]);
	return 0; 
}
