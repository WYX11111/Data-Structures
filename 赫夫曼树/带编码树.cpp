# include <stdio.h>
# include <malloc.h>
# include <iostream.h>
# include <conio.h>
# include <string.h>

# define MAX_LENGTH 100
typedef char **HuffmanCode;

typedef struct
{
	int weight; //权值
	int parent,lchild,rchild; //双亲，左右孩子
}HTNode,*HuffmanTree; //结点和指针

void Select(HuffmanTree HT,int i,int &s1,int &s2)
{ //在建立哈夫曼树的所有结点中选择权值最小的两个结点存放在s1,s2中
	int j,k=1;
	while(HT[k].parent!=0)
		k++;
	s1=k;
	
	for(j=1;j<=i;++j)
		if(HT[j].parent==0&&HT[j].weight<HT[s1].weight)
			s1=j;
	k=1;
	
	while((HT[k].parent!=0||k==s1))
		k++;
	
	s2=k;
	for(j=1;j<=i;++j)
		if(HT[j].parent==0&&HT[j].weight<HT[s2].weight&&j!=s1)
			s2=j;
}

void HuffmanCoding(HuffmanTree &HT,HuffmanCode&HC,int *w,int n)
{ 
	int m,i,s1,s2,start,c,f;
	HuffmanTree p;
	if(n<=1)
		return;
	
	m=2*n-1;//由得到的叶子数而计算结点总数
	HT=(HuffmanTree)malloc((m+1)*sizeof(HTNode));//分配存储空间

	for(p=HT+1,i=1;i<=n;++i,++p,++w)
	{
		p->weight=*w;//为结点初始化权值
		cout<<endl<<"HT["<<i<<"].weight="<<p->weight<<" ";
		p->parent=0;
		p->lchild=0;
		p->rchild=0;
	}

	for(;i<=m;++i,++p)
	{
		p->weight=0;
		p->parent=0;
		p->lchild=0;
		p->rchild=0;
	}//初始化双亲和左右孩子，使他们成为孤立的
	
	cout<<endl<<endl<<"哈弗曼树创建的顺序如下：";
	
	for(i=n+1;i<=m;++i)
	{
		Select(HT,i-1,s1,s2); //调用select函数
		HT[s1].parent=i;
		HT[s2].parent=i;
		HT[i].lchild=s1;
		HT[i].rchild=s2;
		HT[i].weight=HT[s1].weight+HT[s2].weight;//新结点的权值是s1和s2权值的和
		cout<<endl<<"HT["<<s1<<"] + HT["<<s2<<"] =";
		cout<<" HT["<<i<<"], weight="<<HT[i].weight;
	}//每次选择最小的两个结点做左右孩子，权值和为新的结点的权值和，删去连个小的结点

	HC=(HuffmanCode)malloc((n+1)*sizeof(char *));
	char *cd;
	cd=(char *)malloc(n*sizeof(char));
	cd[n-1]='\0';
	cout<<endl<<endl<<"HuffmanTree编码是："<<endl;
	for(i=1;i<=n;++i)//从底下往上寻回编码
	{
		start=n-1;
		for(c=i,f=HT[i].parent;f!=0;c=f,f=HT[f].parent)
			if(HT[f].lchild==c)
				cd[--start]='0';
			else
				cd[--start]='1';
		HC[i]=(char*)malloc((n-start)*sizeof(char));
		strcpy(HC[i],&cd[start]);
		printf("\nHT[%d]: %s",i,HC[i]);
	}
	free(cd);
}

void main()
{ 
	HuffmanTree HT;
	HuffmanCode HC;

	int n,i;
	int *w,W[MAX_LENGTH];

	cout<<"请输入哈弗曼树元素的个数： ";
	cin>>n;
	for(i=0;i<n;++i)
	{
		cout<<"请输入第 "<<i+1<<"个元素的权值:  ";
		cin>>W[i];
	}
	w=W;
	HuffmanCoding(HT,HC,w,n);
}