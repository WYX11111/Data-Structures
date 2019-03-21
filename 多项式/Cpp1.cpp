#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct list
{
	int cishu;
	int xishu;
	struct list *next;
};

typedef struct list L;

L *create1()
{

	int a[3] = {1,-8,1};
	int b[3] = {5,2,0};
	L *head,*node,*end;
	head=(L *)malloc(sizeof(L));
	end=head;
	for(int i = 0; i < 3; i++)
	{
		node=(L *)malloc(sizeof(L));
		node->xishu = a[i];
		node->cishu = b[i];
		end->next=node;
		end = node;
	}

	end->next=NULL;
	return head;
}

L *create2()
{

	int a[3] = {6,-3,-3};
	int b[3] = {5,2,0};
	L *head,*node,*end;
	head=(L *)malloc(sizeof(L));
	end=head;
	for(int i = 0; i < 3; i++)
	{
		node=(L *)malloc(sizeof(L));
		node->xishu = a[i];
		node->cishu = b[i];
		end->next=node;
		end = node;
	}

	end->next=NULL;
	return head;
}

void insert(L *list,int cishu,int xishu)
{
	L *t=list;
	L *in;

	while(t->next != NULL)
	{
		t=t->next;
	}
	if(t!=NULL)
	{
		in=(L *)malloc(sizeof(L));
		
		in->cishu = cishu;
		in->xishu = xishu;
		in->next=t->next;
		t->next=in;
	}
	else{
		printf("节点不存在!");
	}
}

L *add(L *L1, L *L2, L *L3)
{
	int t;
	int flag = 0;
	L *head; 
	while(L2->next != NULL)
	{
		flag = 0;
		L2=L2->next;
		t = L2->cishu;
		head = L3;
		while(head->next!=NULL)
		{
			head=head->next;
			if(head->cishu==t)
			{
				head->xishu += L2->xishu;
				flag = 1;
			}
		}
		if(flag==0)
		{
			insert(head,L2->cishu,L2->xishu);
		}

	}
	return L3;
}

L *sub(L *L1, L *L2, L *L3)
{
	int t;
	L *head; 
	while(L2->next != NULL)
	{
		L2=L2->next;
		t = L2->cishu;
		head = L3;
		while(head->next!=NULL)
		{
			head=head->next;
			if(head->cishu==t)
			{
				head->xishu -= L2->xishu;
			}
		}
	}
	return L3;
}
void show(L *list)
{
	while(list->next!=NULL)
	{
		list=list->next;
		printf("%dx^%d  ",list->xishu,list->cishu);
	}
	printf("\n");
}

int main()
{
	printf("y=x^5-8x^2+1  和  y=6x^5-3x^2-3\n");
int t;
printf("1.+ 2.-\n");
scanf("%d",&t);
if(t==2)
{
	L *L1=NULL;
	L *L2=NULL;
	L *L3=NULL;

	L1 = (L *)malloc(sizeof(L));
	L2 = (L *)malloc(sizeof(L));
	L3 = (L *)malloc(sizeof(L));

	if(L1 == NULL && L2 == NULL)
	{
		printf("error!\n");
		return 0;
	}

	L1=create1();

	L2=create2();

	L3=create1();
	

	L3=sub(L1,L2,L3);

	show(L3);
}
if(t == 1)
{
	L *L1=NULL;
	L *L2=NULL;
	L *L3=NULL;

	L1 = (L *)malloc(sizeof(L));
	L2 = (L *)malloc(sizeof(L));
	L3 = (L *)malloc(sizeof(L));

	if(L1 == NULL && L2 == NULL)
	{
		printf("error!\n");
		return 0;
	}

	L1=create1();

	L2=create2();

	L3=create1();
	

	L3=add(L1,L2,L3);

	show(L3);
}
	return 0;
}