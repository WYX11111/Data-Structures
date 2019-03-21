
#include <stdio.h>
#include <stdlib.h>

#define INFINITY  1107       //最大值∞
#define MAX_VERTEX_NUM      20  //假设的最大顶点数

typedef float VRType;
typedef char VertexType;

typedef struct ArcCell                             //弧（边）结点的定义
{	
	VRType adj;                                    //顶点间关系，无权图取1或0；有权图取权值类型
	//InfoType *info;                              //该弧相关信息的指针
} ArcCell, AdjMatrix [MAX_VERTEX_NUM][MAX_VERTEX_NUM];

typedef struct                                     //图的定义：用两个数组分别存储顶点表和邻接矩阵
{    
	VertexType vexs [MAX_VERTEX_NUM];              //描述顶点的数组
    AdjMatrix arcs;                                //邻接矩阵
    int vexnum, arcnum;                            //顶点总数，弧（边）总数
} Mgraph;

typedef struct
{
	int data;                                       //顶点信息
	int set;   
} VEX;

typedef struct 
{    
	int vexs, vexe;                                 //边依附的两顶点
    VRType score;                                   //边的权值
    int flag;                                       //标志域
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

	printf("请输入顶点个数:");
	scanf("%d",&G.vexnum);

	printf("请输入边的个数:");
	scanf("%d",&G.arcnum);
	fflush(stdin);

	for(i = 0; i < G.vexnum; i++)
	{
		printf("请输入第%d个顶点代表的字符:",i+1);
		scanf("%c",&G.vexs[i]);
		fflush(stdin);
	}

	for(i = 0; i < G.vexnum; i++)			        //初始化邻接矩阵
		for(j = 0; j<G.vexnum; j++)
			G.arcs[i][j].adj = INFINITY;

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
        for(j=i+1; j<G.vexnum; j++)//无向网只寻找邻接矩阵的上半三角就欧克,有向图的话j要从0开始
        {
            if(G.arcs[i][j].adj != INFINITY)//说明边连线存在
            {
                e[k].vexs = i;
                e[k].vexe = j;
                e[k].score = G.arcs[i][j].adj;
				e[k].flag = 0;
				k++;
            }
        }
    }

	//冒泡排序，使权值升序排列
	for (i = 0; i < G.arcnum - 1; i++)
		for(j=0; j < G.arcnum - i - 1; j++)
			if (e[j].score > e[j+1].score)
			{
				EDGE t;
				t = e[j];
				e[j] = e[j+1];
				e[j+1] = t;
			}

    printf("\n最小生成树:");

    k=0;
    j=0;

    while(G.vexnum-1 > k)                           //n个顶点需要n-1条边
    {
        if(v[e[j].vexs].set != v[e[j].vexe].set)    //如果一条边的两个顶点不都在集合中
        {
			printf("(%c,%c)\n",G.vexs[e[j].vexs],G.vexs[e[j].vexe]);

			e[j].flag = 1;

            temp = v[e[j].vexe].set;
            for(i=0; i < G.vexnum; i++)//对所有顶点
            {
                if(v[i].set == temp)
                {
                    v[i].set = v[e[j].vexs].set;
                }
            }
            k++;//已有边数加一
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