#include<stdio.h>
#include<stdlib.h>
#include<string.h>

struct student_info
{
	int no;
    char name[11];
    int grade;
	int time;
};
typedef struct student_info stu;

typedef struct DouNode
{
    stu data;

    struct DouNode *prior,*next;
    
} Node;

DouNode *Create()
{
	DouNode *s,*head,*end;
	end = NULL;
	s = NULL;
	head = (DouNode *)malloc(sizeof(DouNode));

	head->prior = NULL;
	head->next = NULL;

	end = head;

	FILE *fp;
	fp=fopen("in.txt","r");
   
	while(!feof(fp))
	{
		s = (DouNode *)malloc(sizeof(DouNode));

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

void swap(DouNode *p, DouNode *s)
{
	stu temp;
	memcpy(&temp, &(p->data), sizeof(stu));
	memcpy(&(p->data), &(s->data), sizeof(stu));
	memcpy(&(s->data), &temp, sizeof(stu));
}

Node *partition(DouNode *p, DouNode *s) 
{  
	int Key;
	int Key2;
	Key = p->data.grade;
	Key2 = p->data.time;

	while(p->next != s)
	{
		while(p->next != s && (s->data.grade < Key || (s->data.grade == Key && s->data.time > Key2))) 
			s = s->prior;
		if(s->data.grade > Key || (s->data.grade == Key && s->data.time < Key2))
			swap(p,s);
		while(p->next != s && (p->data.grade > Key || (p->data.grade == Key && p->data.time < Key2)))
			p = p->next;  
		if(p->data.grade < Key || p->data.grade == Key && p->data.time > Key2) 
			swap(p,s);
    }
	if(p->data.grade < s->data.grade || (p->data.grade == s->data.grade && p->data.time > s->data.time))
		swap(p,s);
	while(p->data.grade != Key)
		p = p->next;
    return p;
}

void Quicksort(DouNode *head, DouNode *tail)
{
	DouNode *temp = NULL;
	if(head != tail) 
	{
		temp = partition(head,tail);
		if (head != temp)
		{
			Quicksort(head,temp->prior);
		}
		if (tail != temp)
		{
			Quicksort(temp->next,tail);
		}
	}
}

void main()
{
    Node *L;
	L = (DouNode *)malloc(sizeof(DouNode));
    L = Create();                                   
    Quicksort(L->next,L->prior);
    DouNode *p;
	p = (DouNode *)malloc(sizeof(DouNode));
	p = L->next;
	printf("   ID          name      grade    time\n");

	while(p!=L)
	{
		printf("%08d %10s %8d %8d\n", p->data.no, p->data.name, p->data.grade,p->data.time);
		p = p->next;
	}	
}