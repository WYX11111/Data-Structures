#include<stdio.h>
#include<stdlib.h>
#include<math.h>
#include<string.h>

typedef struct node
{
	char c[10];
	int len;       //��¼�ؼ��ֵĳ��� 
	struct node *q;
}keynode;            //�ؼ��ֽ�㣬��Ϊ�ؼ��ֵĳ��Ȳ�����10���ַ� 

typedef struct table
{
	char w;
	keynode *p;
}hash;             //�����ϣ������ 

void init_value(hash key[],char stack[] ,int *information1, int *information2 ) //��ʼ������ 
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

void create_hash(hash *key)         //������ϣ����
{
	int i,num=0,k;                   //num��ʾ�ؼ��ֵ�������k��ʾ�����ؼ��ֵĳ���
	char ch;
	FILE *fp;
	keynode *p1;                //p1Ϊָ��ؼ��ֽ�����͵�ָ��
	for(i=0;i<26;i++)
	{
		key[i].p=NULL;
		key[i].w='a'+i;             //��ϣ��ÿ�������ַ���洢26����ĸ
	}
	if ((fp=fopen("keyword.txt","r"))==NULL)     //��д�йؼ��ֵ��ļ����ļ��洢��C����
	{
		printf("û�д��ļ�\n");
		exit(0);
	}
	while(num<100)                   //����ؼ��ֵĸ�������100
	{
		k=0;
		while(k<10)                  //����ؼ��ֵĳ�������10 
		{
			ch=fgetc(fp);            //���ļ��ж�һ���ַ������ո����˳� 
			if(ch==32)
				break;
			if(k == 0)
				p1=(keynode*)malloc(sizeof(struct node));//�����ǿո����ǹؼ��ֵĵ�һ����ĸ��  �򿪱ٹؼ��ֽ��ռ� 
			p1->c[k]=ch;
			k++;
		}
		p1->c[k++] = '\0';

		i=0;
		while(i<26)         //��һ���ؼ��ֶ���ؼ��ֽ��󣬽��ý�����ӵ���ϣ���� 
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
		if(feof(fp))              //������ļ��Ѷ��꣬��ر��ļ�
	    {
			fclose(fp);
			break;
		}
	}
}

void get_compare1(char stack[],hash key[],int *information1)//�Ӹ�����һ��Դ�����ж��ؼ���,���ùؼ��ִ����ַ�����
{
	FILE *fp;
	char ch;
	int i,j;
	keynode *q1;
	fp=fopen("program1.txt","r");                //�򿪴洢��C�̵�Դ����
	do{
		
		for(i=0;i<10;i++)
			stack[i]='\0';
		i=0;
		while(i<10)            //��ȡʱ��Ϊ�ؼ��ֵĳ���С��10
		{
			ch=fgetc(fp);     //���ļ��ж�ȡʱһ���ַ�һ���ַ������������ո����˳�
			if(ch<'a'||ch>'z')
				break;
			stack[i]=ch;
			i++;                              //��ȡ��һ���ַ�
		}
		i=0;
		while(i<26)                   //���ùؼ������ϣ���еĹؼ��ֱȽ�
		{
			if(stack[0]!=key[i].w)
				i++;
			else
			{
				q1=key[i].p;
				while(q1)
				{
					if(strcmp(stack,q1->c)!=0)//�����ȽϵĹؼ����뵱ǰָ��Ĺؼ��ֲ�ͬ����ָ����һ���ؼ���
						q1=q1->q;
					else    //�����ȽϵĹؼ����뵱ǰָ��Ĺؼ�����ͬ�����Ӧλ�õ�Ƶ����1
					{
						//j=q1->len;
						information1[i]++;
						break;
					}
				}
				break;
			}
		}
	}while(ch!=EOF);                //����Դ�����Ѷ��꣬��ر��ļ�
	fclose(fp);
}

void get_compare2(char stack[],hash key[],int *information2)//�Ӹ�������һ��Դ�����ж��ؼ���,���ùؼ��ִ����ַ�����
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
		while(i<10)            //��ȡʱ��Ϊ�ؼ��ֵĳ���С��10
		{
			ch=fgetc(fp);     //���ļ��ж�ȡʱһ���ַ�һ���ַ������������ո����˳�
			if(ch<'a'||ch>'z')
				break;
			stack[i]=ch;
			i++;                              //��ȡ��һ���ַ�
		}
		i=0;
		while(i<26)                   //���ùؼ������ϣ���еĹؼ��ֱȽ�
		{
			if(stack[0]!=key[i].w)
				i++;
			else
			{
				q1=key[i].p;
				while(q1)
				{
					if(strcmp(stack,q1->c)!=0)//�����ȽϵĹؼ����뵱ǰָ��Ĺؼ��ֲ�ͬ����ָ����һ���ؼ���
						q1=q1->q;
					else    //�����ȽϵĹؼ����뵱ǰָ��Ĺؼ�����ͬ�����Ӧλ�õ�Ƶ����1
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

float similarity(int information1[],int information2[])//���ù������ҷ�������������������ƶ�
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
		i=  n/(l*r);               // i��Ϊ��Դ��������ƶ�
	}
	return(i);
}

int main(void)
{
	float i;
	hash key[100];           //����һ��hash�ṹ������ռ䣬�������д��26����ĸ
	char stack[10];          //����һ���ַ�����ռ䣬���д�Ŵ��Ƚ�Դ����Ĺؼ���
	int information1[26],information2[26];
	printf("************************************************\n\n");
	init_value(key,stack,information1,information2);             //��ʼ������
	printf("������ϣ��:\n");
	create_hash(key);                                         //������ϣ��

	printf("�ȽϹ�ϣ��1\n");
	get_compare1(stack,key,information1);                   //�Ƚϵ�һ��Դ����
	
	printf("�ȽϹ�ϣ��2\n");
	get_compare2(stack,key,information2);                  //�Ƚϵڶ���Դ����

	printf("�������ƶ�\n");
	i=similarity(information1,information2);                //�������ƶ�

	printf("\n������������ƶ�Ϊ:     %f\n\n",i);
	printf("************************************************\n\n");
	return 0;
}
