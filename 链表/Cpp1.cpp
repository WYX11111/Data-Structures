#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct list
{
	int data;
	struct list *next;
};

typedef struct list L;

L *create()
{
	int k;
	char c;
	L *head,*node,*end;
	head=(L *)malloc(sizeof(L));
	end=head;
	printf("��������:�� �ո�ָ����س�������");

	while(1)
	{
		scanf("%d%c",&k,&c);
		node=(L *)malloc(sizeof(L));
		node->data=k;
		end->next=node;
		end = node;
		if(c=='\n')
			break;
	}
	head->data=NULL;
	end->next=NULL;
	return head;
}

void insert(L *list,int n)
{
	L *t=list;
	L *in;
	int i=0;

	while(i<n&&t!=NULL)
	{
		t=t->next;
		i++;
	}
	if(t!=NULL)
	{
		in=(L *)malloc(sizeof(L));
		printf("����Ҫ���������:");
		scanf("%d",&in->data);
		in->next=t->next;
		t->next=in;
	}
	else{
		printf("�ڵ㲻����!");
	}
}

void delet(L *list,int n)
{
	L *t=list;
	L *in;
	int i=0;

	while(i<n&&t!=NULL)
	{
		in=t;
		t=t->next;
		i++;
	}
	if(t!=NULL)
	{
		in->next=t->next;
		free(t);
	}
	else{
		printf("�ڵ㲻����!");
	}
}

void find(L *list,int n)
{
	int i=1;
	while(list->next!=NULL)
	{
		list=list->next;
		if(i==n)
		{
			printf("��%d��������%d\n",n,list->data);
			break;
		}
		i++;
	}
	if(list==NULL)
	{
		printf("�ڵ㲻����!");
	}
}

int locate(L *list,int t)
{
	int i=1;
	while(list->next!=NULL && list->next->data != t)
	{
		list=list->next;
		i++;
	}
	return i;
}

int length(L *list)
{
	int i=0;
	while(list->next!=NULL)
	{
		list=list->next;
		i++;
	}
	return i;
}

void f(L* La, L* Lb, int i, int j)  //������ͷ�ڵ�
{
	L *p = La;
	L *q = La->next;
	L *r = Lb;
	L *m;
	int n=0;

	while(n < i)
	{
		p = p->next;
		q = q->next;
		n++;
	}

	n = 0;

	while(n < j)
	{
		r = r->next;
		n++;
	}

	Lb->next = p;

	p->next = r;
	
	while(q)
	{
		m = q;
		q = q->next;
		free(m);
	}
}

void delet_all(L *list)
{
	L *p;
	while(list)
	{
		p=list->next;
		free(list);
		list = p;
	}
}

void clear(L *list)
{
	L *p,*q;
	p = list->next;
	while(p != NULL)
	{
		q = p->next;
		free(p);
		p = q;
	}
	list->next = NULL;
}

int pr(L *list,int n)
{
	L *p;
	while(list->next!=NULL)
	{
		p = list;
		list=list->next;
		if(list->data == n)
		{
			break;
		}
	}
	if(list==NULL || p->data == NULL)
	{
		printf("���ݲ�����!");
		return NULL;
	}
	return p->data;
}

int next(L *list,int n)
{
	while(list->next!=NULL)
	{
		list=list->next;
		if(list->data == n)
		{
			break;
		}
	}
	list = list->next;
	if(list==NULL)
	{
		printf("���ݲ�����!");
		return NULL;
	}
	return list->data;
}

int check(L *list)
{
	if(list->next == NULL)
		return 1;
	else return 0;
}

void show(L *list)
{
	while(list->next!=NULL)
	{
		list=list->next;
		printf("%d   ",list->data);
	}
	printf("\n");
}
/*
int main()
{
	L *head=NULL;
	int i,l,t;
	head=(L *)malloc(sizeof(L));
	if(head==NULL)
	{
		printf("error!\n");
		return 0;
	}

	head=create();

	while(1){
		printf("ѡ����\n");
		printf("1.����\n");
		printf("2.����\n");
		printf("3.��ȡԪ��\n");
		printf("4.��λ\n");
		printf("5.ɾ��\n");
		printf("6.���\n");
		printf("7.���\n");
		printf("8.����\n");
		printf("9.Ѱ����һ��Ԫ��\n");
		printf("10.Ѱ����һ��Ԫ��\n");
		printf("11.�ж��Ƿ�Ϊ��\n");
		scanf("%d",&i);
		switch(i)
		{
		    case 1:
				insert(head,l);
				break;

			case 2:
				l=length(head);
				printf("������Ϊ%d\n",l);
			
			case 3:
				printf("��������������±�:");
				scanf("%d",&t);
				find(head,t);
				break;

			case 4:
				printf("�����������е�һ������:");
				scanf("%d",&t);
				printf("%d��%d�ڸ�����",t,locate(head,t));
				break;

			case 5:
				printf("������ɾ�������±�:");
				scanf("%d",&t);
				delet(head,t);
				break;

			case 6:
				show(head);
				break;

			case 7:
				clear(head);
				break;

			case 8:
				delet_all(head);
				break;

			case 9:
				printf("�����������е�һ������:");
				scanf("%d",&t);
				printf("%d����һ������Ϊ%d",t,pr(head,t));
				break;
			
			case 10:
				printf("�����������е�һ������:");
				scanf("%d",&t);
				printf("%d����һ������Ϊ%d",t,next(head,t));

			case 11:
				t = check(head);
				if(t == 1)
					printf("��");
				if(t == 0)
					printf("�ǿ�");

			default:
				break;
		}
	}
	return 0;
}*/

int main()
{
	L *head1=NULL;
	L *head2=NULL;

	head1=(L *)malloc(sizeof(L));
	head2=(L *)malloc(sizeof(L));

	head1=create();
	head2=create();

	show(head1);
	printf("\n");
	show(head2);
	printf("\n");

	f(head1,head2,1,1);

	show(head2);
	return 0;
}