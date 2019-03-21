#include <stdio.h>
#include <stdlib.h>

#define OK 1
#define ERROR 0

typedef struct CSNode{
	char data;
	struct CSNode* firstchild;
	struct CSNode* nextsibling;	
}CSNode,*CSTree;

int CreateTree_CS(CSTree &T)
{
	char ch;
	scanf("%c",&ch);
	
	if(ch=='#')
	{
		T=NULL;
	}

	else
	{
		T=(CSTree)malloc(sizeof(CSNode));
		
		if(!T) exit(0);
		
		T->data=ch;
		CreateTree_CS(T->firstchild);
		CreateTree_CS(T->nextsibling);
	}
	return OK;
}

//树的度 
int Algo_1(CSTree T){
	int i,j,max,tmp;
	CSTree Q[100];//临时存放各结点 
	i=j=0;
	max=-1;
	if(T)
	{
		max=0;
		Q[j++]=T->firstchild;
		
		while(i<j)//按层序遍历 
		{
			tmp=0;
			while(Q[i])
			{
				tmp++;
				//存储有孩子的结点 
				if(Q[i]->firstchild) Q[j++]=Q[i]->firstchild;
				Q[i]=Q[i]->nextsibling;//统计本层结点数 
			}
			if(tmp>max) max=tmp;
			i++;
		}
	}
	return max;
} 
 
 
//树的深度
int Algo_2(CSTree T){
	int row,max;
	stack<CSTree> S;
	CSTree tmp;
	row=0;
	if(T)
	{
		S.push(T);
		row=max=1;
		
		while(!S.empty())
		{
			tmp=S.top();
			while(tmp->firstchild)
			{
				S.push(tmp->firstchild);
				++max;
				if(row<max) row=max;
				tmp=S.top();
			}
			tmp=S.top();
			S.pop();
			if(tmp->nextsibling)
				S.push(tmp->nextsibling);
			else{
				while(!S.empty())
				{
					tmp=S.top();
					S.pop();
					--max;
					
					if(tmp->nextsibling){
						S.push(tmp->nextsibling);
						break;
					}
				}
			}
		}
	}
	return row;
}
 
 
//树的叶子 
int Algo_3(CSTree T){
	if(T)
	{
		if(!T->firstchild){
		cout<<T->data<<' ';//输出叶子结点 
		return 1+Algo_3(T->nextsibling);
		}
		else return Algo_3(T->firstchild)+Algo_3(T->nextsibling);
	}
	else return 0;
}
 
 
//树的边
void Algo_4(CSTree T){
	CSTree p,q;
	if(T)
	{
		p=T;
		q=T->firstchild;
		int i=0;//打印计数器 
		while(q)
		{
			printf("(%c,%c) ",p->data,q->data);
			q=q->nextsibling;
			i++;
		}
		if(i>0) cout<<endl;
		Algo_4(T->firstchild);
		Algo_4(T->nextsibling);
	}
}
 
 
int main()
{
	CSTree T;
	InitTree_CS(T);
	printf("请录入先序序列(扩展法、前序): 例如：RAD^E^^B^CFG^H^K^^^^^\n");
	CreateTree_CS(T);
	
	
	cout<<"****度****"<<endl; 
	cout<<"树的度（结点的最大度）为:"<<Algo_1(T)<<endl<<endl<<endl;
	
	
	cout<<"****深度****"<<endl;
	cout<<"树的深度为:"<<Algo_2(T)<<endl<<endl<<endl;
	
	
	cout<<"****叶子****"<<endl; 
	cout<<"叶子结点分别为:"<<endl;
	cout<<"个数为:"<<Algo_3(T)<<endl<<endl<<endl;
	
	
	cout<<"****边****"<<endl;
	cout<<"下面输出所有边："<<endl;
	Algo_4(T);
	cout<<endl;
	return 0;
} 
