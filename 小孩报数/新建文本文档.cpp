#include <iostream>

using namespace std;

struct Node
{
	char data[20];
	int num;
	Node *next;
};

class Linklist
{
public:
	Node * Head;
public:
	Linklist();
	void CreatList(int k);
	void Delete(Node *a);
	void Link();
	void Display();
};

Linklist::Linklist()
{
	Head = new Node;
	Head->next = NULL;
}

void Linklist::CreatList(int k)
{
	int i,j;
	char s[20];
	Node *p;
	Node *temp;
	p = Head;
	
	for(i = 0; i < k; i++)
	{
		cin >> s;
		temp = new Node;
		for (j = 0; s[j]; j++)
			temp->data[j] = s[j];
		temp->data[j] = '\0';
		temp->num = i;
		temp->next = NULL;
		
		p->next = temp;
		p = temp;
	}
}

void Linklist::Delete(Node *a)
{
	Node *temp;
	temp = Head->next;
	while (temp->next->num != a->num)
	{
		temp = temp->next;
	}
	cout << temp->next->data << endl;
	temp->next = temp->next->next;
}

void Linklist::Link(){
	Node *temp;
	temp = Head->next;
	
	while (temp->next) 
	{		
		temp = temp->next;
	}
	temp->next = Head->next;
}

void Linklist::Display(){
	Node *temp;
	temp = Head->next;
	
	if(temp)
	{
		cout << temp->data;	
		temp = temp->next;

		while (temp) 
		{		
	
			cout << " " << temp->data;		
			temp = temp->next;
		}
	}
	else cout << "NULL";
}

int main()
{
	int w,s,i,j,k;
	Linklist list1;
	cin >> k;
	list1.CreatList(k);
	list1.Link();

	Node *a;
	a = list1.Head->next;

	cin >> w;
	if(w >= n)
		return 0;
	if(cin.get()==',')
		cin >> s;
	
	if(w == 1)
	{
		for(j = 1; j < k; j++)
				a = a->next;
	}

	for(i = 0; i < w-2; i++)
		a = a->next;

	for(j = 1; j < k; j++)
	{
		for(i = 0; i < s-1; i++)
			a = a->next;
		list1.Delete(a->next);
	}
	cout << a->data << endl;
	return 0;
}