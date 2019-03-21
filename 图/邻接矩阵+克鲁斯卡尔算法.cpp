
#include <stdio.h>
#include <stdlib.h>

#define INFINITY  1107       //���ֵ��
#define MAX_VERTEX_NUM      20  //�������󶥵���

typedef float VRType;
typedef char VertexType;

typedef struct ArcCell                             //�����ߣ����Ķ���
{	
	VRType adj;                                    //������ϵ����Ȩͼȡ1��0����ȨͼȡȨֵ����
	//InfoType *info;                              //�û������Ϣ��ָ��
} ArcCell, AdjMatrix [MAX_VERTEX_NUM][MAX_VERTEX_NUM];

typedef struct                                     //ͼ�Ķ��壺����������ֱ�洢�������ڽӾ���
{    
	VertexType vexs [MAX_VERTEX_NUM];              //�������������
    AdjMatrix arcs;                                //�ڽӾ���
    int vexnum, arcnum;                            //���������������ߣ�����
} Mgraph;

typedef struct
{
	int data;                                       //������Ϣ
	int set;   
} VEX;

typedef struct 
{    
	int vexs, vexe;                                 //��������������
    VRType score;                                   //�ߵ�Ȩֵ
    int flag;                                       //��־��
} EDGE;

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
	float w;

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
			G.arcs[i][j].adj = INFINITY;

	printf("���������ڶ��㼰��Ȩֵ���ո���,��:A B 11.7����\n");

	for(int k = 0; k < G.arcnum; k++)
	{
		scanf("%c %c %f",&v1,&v2,&w);
		fflush(stdin);

		i = locatevex(G,v1);
		j = locatevex(G,v2);
		if (i == G.vexnum || j == G.vexnum)
			printf("���㲻����\n");
		else
		{
			G.arcs[i][j].adj = w;
			G.arcs[j][i].adj = w;
		}
	}
}

void print_all(Mgraph &G)
{
	int i,j;
	for (i = 0; i < G.vexnum; i++)
		printf("%7c",G.vexs[i]);

	for (i = 0; i < G.vexnum; i++)
	{
		printf("\n%c   ",G.vexs[i]);

		for (j = 0; j < G.vexnum; j++)
		{
			if(G.arcs[i][j].adj == INFINITY)
				printf("***    ");
			else printf("%-7.1f",G.arcs[i][j].adj);
		}
	}
}

void Kruscal(Mgraph &G)
{
	EDGE *e;
	VEX *v;

	int i, j, temp, k = 0;
	e = new EDGE[G.arcnum];
	v = new VEX[G.vexnum];

	for(i = 0; i < G.vexnum; i++)
	{
		v[i].data = i;
		v[i].set = i;
	}

	for(i=0; i<G.vexnum; i++)
    {
        for(j=i+1; j<G.vexnum; j++)//������ֻѰ���ڽӾ�����ϰ����Ǿ�ŷ��,����ͼ�Ļ�jҪ��0��ʼ
        {
            if(G.arcs[i][j].adj != INFINITY)//˵�������ߴ���
            {
                e[k].vexs = i;
                e[k].vexe = j;
                e[k].score = G.arcs[i][j].adj;
				e[k].flag = 0;
				k++;
            }
        }
    }

	//ð������ʹȨֵ��������
	for (i = 0; i < G.arcnum - 1; i++)
		for(j=0; j < G.arcnum - i - 1; j++)
			if (e[j].score > e[j+1].score)
			{
				EDGE t;
				t = e[j];
				e[j] = e[j+1];
				e[j+1] = t;
			}

    printf("\n��С������:");

    k=0;
    j=0;

    while(G.vexnum-1 > k)                           //n��������Ҫn-1����
    {
        if(v[e[j].vexs].set != v[e[j].vexe].set)    //���һ���ߵ��������㲻���ڼ�����
        {
			printf("(%c,%c)\n",G.vexs[e[j].vexs],G.vexs[e[j].vexe]);

			e[j].flag = 1;

            temp = v[e[j].vexe].set;
            for(i=0; i < G.vexnum; i++)//�����ж���
            {
                if(v[i].set == temp)
                {
                    v[i].set = v[e[j].vexs].set;
                }
            }
            k++;//���б�����һ
        }
		else
			e[j].flag = 2;

        j++;
    }
}

void main()
{
	Mgraph G;
	create(G);

//	print_all(G);
	
	Kruscal(G);
}