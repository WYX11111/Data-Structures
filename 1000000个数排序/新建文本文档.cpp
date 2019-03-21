#include<stdio.h>
#include<stdlib.h>
#include<time.h>

#define RAND_MAX 2147483647

typedef struct Node
{
    int data;

    struct Node *prior,*next;
    
} Node;

Node *Create()
{
	Node *s,*head,*end;
	end = NULL;
	s = NULL;
	head = (Node *)malloc(sizeof(Node));

	head->prior = NULL;
	head->next = NULL;

	end = head;

	srand(time(NULL)); 

	for(int i = 0; i < 1000000; ++i)
	{
		s = (Node *)malloc(sizeof(Node));

		s->data = rand();
        
		s->next = head;
		s->prior = end;
		end->next = s;
		end = s;
	}

	head->prior = end;
	
	return head;
}

void swap(int *p, int *s)
{
	int temp;
	temp = *p;
	*p = *s;
	*s = temp;
	
}

Node *partition(Node *p, Node *s) 
{   
	int privotKey;
	privotKey = p->data;
	while(p->next != s)
	{
		while(p->next != s && s->data <= privotKey) 
			s = s->prior;
		if(s->data > privotKey)
			swap((&p->data),(&s->data));
		while(p->next != s && p->data >= privotKey)
			p = p->next;
		if(p->data < privotKey) 
			swap((&p->data),(&s->data));
    }
	if(p->data < s->data)
		swap((&p->data),(&s->data));
	while(p->data != privotKey)
		p = p->next;
    return p;
}

void Quicksort(Node *head, Node *tail)
{
	Node *temp = NULL;
	if(head!=tail) 
	{
		temp = partition(head,tail);
		if ( head!=temp )
		{
			Quicksort(head,temp->prior);
		}
		if ( tail != temp )
		{
			Quicksort(temp->next,tail);
		}
	}
}

void main()
{
	clock_t start,stop;
	double s;

	start = clock();

for (int i = 0; i < 20; ++i)
{
	Node *L;
	L = (Node *)malloc(sizeof(Node));
    L = Create();                                   
    Quicksort(L->next,L->prior);
	
	Node *p = L->next;
}
	stop = clock();

	s = (stop - start)/(double)CLK_TCK/10.0;

	printf("20次所用平均时间%lfs",s);
}