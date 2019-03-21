# include <stdio.h>
# include <malloc.h>
# include <iostream.h>
# include <conio.h>
# include <string.h>

# define MAX_LENGTH 100
typedef char **HuffmanCode;

typedef struct
{
	int weight; //Ȩֵ
	int parent,lchild,rchild; //˫�ף����Һ���
}HTNode,*HuffmanTree; //����ָ��

void Select(HuffmanTree HT,int i,int &s1,int &s2)
{ //�ڽ����������������н����ѡ��Ȩֵ��С�������������s1,s2��
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
	
	m=2*n-1;//�ɵõ���Ҷ����������������
	HT=(HuffmanTree)malloc((m+1)*sizeof(HTNode));//����洢�ռ�

	for(p=HT+1,i=1;i<=n;++i,++p,++w)
	{
		p->weight=*w;//Ϊ����ʼ��Ȩֵ
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
	}//��ʼ��˫�׺����Һ��ӣ�ʹ���ǳ�Ϊ������
	
	cout<<endl<<endl<<"��������������˳�����£�";
	
	for(i=n+1;i<=m;++i)
	{
		Select(HT,i-1,s1,s2); //����select����
		HT[s1].parent=i;
		HT[s2].parent=i;
		HT[i].lchild=s1;
		HT[i].rchild=s2;
		HT[i].weight=HT[s1].weight+HT[s2].weight;//�½���Ȩֵ��s1��s2Ȩֵ�ĺ�
		cout<<endl<<"HT["<<s1<<"] + HT["<<s2<<"] =";
		cout<<" HT["<<i<<"], weight="<<HT[i].weight;
	}//ÿ��ѡ����С��������������Һ��ӣ�Ȩֵ��Ϊ�µĽ���Ȩֵ�ͣ�ɾȥ����С�Ľ��

	HC=(HuffmanCode)malloc((n+1)*sizeof(char *));
	char *cd;
	cd=(char *)malloc(n*sizeof(char));
	cd[n-1]='\0';
	cout<<endl<<endl<<"HuffmanTree�����ǣ�"<<endl;
	for(i=1;i<=n;++i)//�ӵ�������Ѱ�ر���
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

	cout<<"�������������Ԫ�صĸ����� ";
	cin>>n;
	for(i=0;i<n;++i)
	{
		cout<<"������� "<<i+1<<"��Ԫ�ص�Ȩֵ:  ";
		cin>>W[i];
	}
	w=W;
	HuffmanCoding(HT,HC,w,n);
}