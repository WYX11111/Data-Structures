#include "stdio.h"
#include "stdlib.h"
#define OK 1
#define ERROR 0
#define OVERFLOW -2

typedef char TElemType;
typedef int Status;
typedef struct CSNode { // 结点结构
 TElemType data;
 struct CSNode *firstchild, *nextsibiling; // 孩子兄弟指针
} BiTNode, *BiTree;

//建立二叉树存储结构，空节点输入作为#结束标识
Status CreateBiTree(BiTree &T) 
{
	char ch;
	scanf("%c",&ch);
	FILE *fp;	
	fp=fopen("d:\\test.txt","w");
	if(fp==NULL)
	{
	printf("create file failed\n");
	return -1;
	}
	if(ch=='#') T=NULL;
	else{
		if(!(T=(BiTNode*)malloc(sizeof(BiTNode))))
			exit(OVERFLOW);
		T->data=ch;
		fprintf(fp,"%c",ch);
		CreateBiTree(T->firstchild);
		CreateBiTree(T->nextsibiling);
	}	
	fclose(fp);
	return OK;

} // CreateBiTree

void Preorder(BiTree T)
{
	if(T)
	 {
		printf("%c",T->data);
		Preorder(T->firstchild);
		Preorder(T->nextsibiling);
	} 
} 

	

	

	

