#include <stdio.h>
#include <stdlib.h>

#define INFINITY  INT_MAX       //���ֵ��
#define MAX_VERTEX_NUM      20  //�������󶥵���

typedef int VRType;
typedef char VertexType

typedef enum 
{
	DG, DN, AG,AN 
} GraphKind;                                       //�� ��/����ͼ������/������

typedef struct ArcCell                             //�����ߣ����Ķ���
{	
	VRType adj;                                    //������ϵ����Ȩͼȡ1��0����ȨͼȡȨֵ����
	InfoType *info;                                //�û������Ϣ��ָ��
} ArcCell, AdjMatrix [MAX_VERTEX_NUM][MAX_VERTEX_NUM];

typedef struct{                                    //ͼ�Ķ��壺����������ֱ�洢�������ڽӾ���
{    
	VertexType vexs [MAX_VERTEX_NUM];              //�������������
    AdjMatrix arcs;                                //�ڽӾ���
    int vernum, arcnum;                            //���������������ߣ�����
    GraphKind kind;                                //ͼ�������־
} Mgraph;