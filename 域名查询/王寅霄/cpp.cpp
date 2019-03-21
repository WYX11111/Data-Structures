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

//���Ķ� 
int Algo_1(CSTree T){
	int i,j,max,tmp;
	CSTree Q[100];//��ʱ��Ÿ���� 
	i=j=0;
	max=-1;
	if(T)
	{
		max=0;
		Q[j++]=T->firstchild;
		
		while(i<j)//��������� 
		{
			tmp=0;
			while(Q[i])
			{
				tmp++;
				//�洢�к��ӵĽ�� 
				if(Q[i]->firstchild) Q[j++]=Q[i]->firstchild;
				Q[i]=Q[i]->nextsibling;//ͳ�Ʊ������� 
			}
			if(tmp>max) max=tmp;
			i++;
		}
	}
	return max;
} 
 
 
//�������
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
 
 
//����Ҷ�� 
int Algo_3(CSTree T){
	if(T)
	{
		if(!T->firstchild){
		cout<<T->data<<' ';//���Ҷ�ӽ�� 
		return 1+Algo_3(T->nextsibling);
		}
		else return Algo_3(T->firstchild)+Algo_3(T->nextsibling);
	}
	else return 0;
}
 
 
//���ı�
void Algo_4(CSTree T){
	CSTree p,q;
	if(T)
	{
		p=T;
		q=T->firstchild;
		int i=0;//��ӡ������ 
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
	printf("��¼����������(��չ����ǰ��): ���磺RAD^E^^B^CFG^H^K^^^^^\n");
	CreateTree_CS(T);
	
	
	cout<<"****��****"<<endl; 
	cout<<"���Ķȣ��������ȣ�Ϊ:"<<Algo_1(T)<<endl<<endl<<endl;
	
	
	cout<<"****���****"<<endl;
	cout<<"�������Ϊ:"<<Algo_2(T)<<endl<<endl<<endl;
	
	
	cout<<"****Ҷ��****"<<endl; 
	cout<<"Ҷ�ӽ��ֱ�Ϊ:"<<endl;
	cout<<"����Ϊ:"<<Algo_3(T)<<endl<<endl<<endl;
	
	
	cout<<"****��****"<<endl;
	cout<<"����������бߣ�"<<endl;
	Algo_4(T);
	cout<<endl;
	return 0;
} 
