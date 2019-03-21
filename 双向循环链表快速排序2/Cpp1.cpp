#include<stdio.h>
#include<stdlib.h>

struct student
{
	int no;
    char name[11];
    int grade;
	int time;
};
typedef struct student STUINFO;

typedef struct Node
{
    STUINFO data;

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

	FILE *fp;
	fp=fopen("in.txt","r");
   
	while(!feof(fp))
	{
		s = (Node *)malloc(sizeof(Node));

        fscanf(fp,"%d %s %d %d",&s->data.no,s->data.name,&s->data.grade,&s->data.time);
		
		s->next = head;
		s->prior = end;
		end->next = s;
		end = s;
	}
	fclose(fp);

	head->prior = end;
	
	return head;
}

void swap(STUINFO *p, STUINFO *s)
{
	STUINFO temp;
	temp = *p;
	*p = *s;
	*s = temp;
	
}

void CheckTime(Node *p)
{
	Node *r = p->next->next;
	Node *q;
	while(r != p)
	{
		q = r;
		while(q->data.grade == q->prior->data.grade)
		{
			if(q->data.time < q->prior->data.time)
				swap((&q->data),(&q->prior->data));
			q = q->prior;
		}
		r = r->next;
	}
}

Node *partition(Node *p, Node *s) 
{  
	int privotKey;
	privotKey = p->data.grade;
	while(p->next != s)
	{
		while(p->next != s && s->data.grade <= privotKey) 
			s = s->prior;
		if(s->data.grade > privotKey)
			swap((&p->data),(&s->data));
		while(p->next != s && p->data.grade >= privotKey)
			p = p->next;  
		if(p->data.grade < privotKey) 
			swap((&p->data),(&s->data));
    }
	if(p->data.grade < s->data.grade)
		swap((&p->data),(&s->data));
	while(p->data.grade != privotKey)
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
    Node *L;
	L = (Node *)malloc(sizeof(Node));
    L = Create();                                   
    Quicksort(L->next,L->prior);
	CheckTime(L);
    Node *p;
	p = (Node *)malloc(sizeof(Node));
	p = L->next;
	printf("   ID          name      grade    time\n");

	while(p!=L)
	{
		printf("%08d %10s %8d %8d\n", p->data.no, p->data.name, p->data.grade,p->data.time);
		p = p->next;
	}	
}