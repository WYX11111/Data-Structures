#include<stdio.h>
#include<stdlib.h>
#include<math.h>
#include<string.h>

typedef struct node
{
	char c[10];
	int len;       //记录关键字的长度 
	struct node *q;
}keynode;            //关键字结点，认为关键字的长度不超过10个字符 

typedef struct table
{
	char w;
	keynode *p;
}hash;             //定义哈希表类型 

void init_value(hash key[],char stack[] ,int *information1, int *information2 ) //初始化函数 
{
	int i;
	for(i=0;i<100;i++)
		key[i].p=NULL;
	for(i=0;i<10;i++)
		stack[i]='\0';
	for(i=0;i<26;i++)
	{
		information1[i]=0;
		information2[i]=0;
	}
}

void create_hash(hash *key)         //创建哈希表函数
{
	int i,num=0,k;                   //num表示关键字的数量，k表示单个关键字的长度
	char ch;
	FILE *fp;
	keynode *p1;                //p1为指向关键字结点类型的指针
	for(i=0;i<26;i++)
	{
		key[i].p=NULL;
		key[i].w='a'+i;             //哈希表每个结点的字符域存储26个字母
	}
	if ((fp=fopen("keyword.txt","r"))==NULL)     //打开写有关键字的文件，文件存储在C盘上
	{
		printf("没有打开文件\n");
		exit(0);
	}
	while(num<100)                   //假设关键字的个数少于100
	{
		k=0;
		while(k<10)                  //假设关键字的长度少于10 
		{
			ch=fgetc(fp);            //从文件中读一个字符，遇空格则退出 
			if(ch==32)
				break;
			if(k == 0)
				p1=(keynode*)malloc(sizeof(struct node));//若不是空格，且是关键字的第一个字母，  则开辟关键字结点空间 
			p1->c[k]=ch;
			k++;
		}
		p1->c[k++] = '\0';

		i=0;
		while(i<26)         //将一个关键字读入关键字结点后，将该结点链接到哈希表上 
		{
			if(p1->c[0]!=key[i].w)
				i++;
			else
			{
				key[i].p=(keynode*)malloc(sizeof(struct node));
				memcpy(key[i].p,p1,sizeof(struct node));
				key[i].p->q=NULL;
				key[i].p->len=k;
				key[i].p->q=NULL;
				break;
			}
		}
		
		num++;
		if(feof(fp))              //如果该文件已读完，则关闭文件
	    {
			fclose(fp);
			break;
		}
	}
}

void get_compare1(char stack[],hash key[],int *information1)//从给出的一个源程序中读关键字,将该关键字存入字符数组
{
	FILE *fp;
	char ch;
	int i,j;
	keynode *q1;
	fp=fopen("program1.txt","r");                //打开存储在C盘的源程序
	do{
		
		for(i=0;i<10;i++)
			stack[i]='\0';
		i=0;
		while(i<10)            //读取时认为关键字的长度小于10
		{
			ch=fgetc(fp);     //从文件中读取时一个字符一个字符来读，遇到空格则退出
			if(ch<'a'||ch>'z')
				break;
			stack[i]=ch;
			i++;                              //读取下一个字符
		}
		i=0;
		while(i<26)                   //将该关键字与哈希表中的关键字比较
		{
			if(stack[0]!=key[i].w)
				i++;
			else
			{
				q1=key[i].p;
				while(q1)
				{
					if(strcmp(stack,q1->c)!=0)//若待比较的关键字与当前指向的关键字不同，则指向下一个关键字
						q1=q1->q;
					else    //若待比较的关键字与当前指向的关键字相同，则对应位置的频数加1
					{
						//j=q1->len;
						information1[i]++;
						break;
					}
				}
				break;
			}
		}
	}while(ch!=EOF);                //若该源程序已读完，则关闭文件
	fclose(fp);
}

void get_compare2(char stack[],hash key[],int *information2)//从给出的另一个源程序中读关键字,将该关键字存入字符数组
{
	FILE *fp;
	char ch;
	int i,j;
	keynode *q1;
	fp=fopen("program2.txt","r");
	do{
		
		for(i=0;i<10;i++)
			stack[i]='\0';
		i=0;
		while(i<10)            //读取时认为关键字的长度小于10
		{
			ch=fgetc(fp);     //从文件中读取时一个字符一个字符来读，遇到空格则退出
			if(ch<'a'||ch>'z')
				break;
			stack[i]=ch;
			i++;                              //读取下一个字符
		}
		i=0;
		while(i<26)                   //将该关键字与哈希表中的关键字比较
		{
			if(stack[0]!=key[i].w)
				i++;
			else
			{
				q1=key[i].p;
				while(q1)
				{
					if(strcmp(stack,q1->c)!=0)//若待比较的关键字与当前指向的关键字不同，则指向下一个关键字
						q1=q1->q;
					else    //若待比较的关键字与当前指向的关键字相同，则对应位置的频数加1
					{
						//j=q1->len;
						information2[i]++;
						break;
					}
				}
				break;
			}
		}
	}while(ch!=EOF);
	fclose(fp);
}

float similarity(int information1[],int information2[])//利用广义余弦法计算这两个程序的相似度
{
	int k=0,m=0,n=0,p=0,q=0;
	float r,l,i;
	while (k<26)
	{
		n+=information1[k]*information2[m];
		p+=information1[k]*information1[k];
		q+=information2[m]*information2[m];

		k++;
		m++;
		r= sqrt (p);
		l= sqrt (q);
		i=  n/(l*r);               // i即为两源程序的相似度
	}
	return(i);
}

int main(void)
{
	float i;
	hash key[100];           //建立一个hash结构的数组空间，该数组中存放26个字母
	char stack[10];          //建立一个字符数组空间，其中存放待比较源程序的关键字
	int information1[26],information2[26];
	printf("************************************************\n\n");
	init_value(key,stack,information1,information2);             //初始化数组
	printf("创建哈希表:\n");
	create_hash(key);                                         //创建哈希表

	printf("比较哈希表1\n");
	get_compare1(stack,key,information1);                   //比较第一个源程序
	
	printf("比较哈希表2\n");
	get_compare2(stack,key,information2);                  //比较第二个源程序

	printf("计算相似度\n");
	i=similarity(information1,information2);                //计算相似度

	printf("\n两个程序的相似度为:     %f\n\n",i);
	printf("************************************************\n\n");
	return 0;
}
