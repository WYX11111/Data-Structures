#include <stdio.h>
#include <stdlib.h>

typedef int ElemType;

typedef struct
{
	ElemType key;
}Node;

typedef struct
{
	Node *r;
	int length;
}HeapType;

void HeapAdjust (HeapType &H, int s, int m)
{
	int j;
	Node rc = H.r[s];             // �ݴ�����ļ�¼
    for(j = 2*s; j <= m; j*=2 )
	{
		if ( j<m && H.r[j].key<H.r[j+1].key )
			++j;  // jΪkey�ϴ��Ӽ�¼���±�
		if ( rc.key >= H.r[j].key )
			break;     // ����Ҫ����
        H.r[s] = H.r[j];  s = j;  // �Ѵ�ؼ��ּ�¼���ϵ�   
	}
	H.r[s] = rc;             // ����ɸѡ�����ļ�¼
}


void HeapSort (HeapType &H)
{
	int i;
	Node w;
	for ( i=H.length/2; i>0; --i )
		HeapAdjust ( H, i, H.length );  
	w=H.r[1] ; H.r[1]= H.r[H.length]; H.r[H.length]=w;     //����"�Ѷ�"��"�ѵ�"�ļ�¼
	for ( i=H.length-1; i>1; --i ) 
	{
		HeapAdjust(H,1,i);
		w=H.r[1]; H.r[1]=H.r[i]; H.r[i]=w;
	}
}

void main()
{
	HeapType H;
	int i;
	printf("����:");
	scanf("%d",&H.length);
	H.r = new Node[H.length+1];
	for(i = 1; i <= H.length; i++)
	{
		scanf("%d",&H.r[i].key);
	}
	HeapSort(H);
	for(i = 1; i <= H.length; i++)
	{
		printf("%d ",H.r[i].key);
	}
}