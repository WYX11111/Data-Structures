#include <iostream>
using namespace std;

const LIST_INIT_SIZE=100;
const LISTINCREMENT=sizeof(char);

typedef struct {
    char *elem;
    int length;
    int listsize;
    int incrementsize;
}SqList;

void InitList(SqList &L, int maxsize=LIST_INIT_SIZE,int incresize=LISTINCREMENT) //����һ��int�Ϳյ����Ա�
{
    L.elem=new char[maxsize];
    L.length=0;
    L.listsize=maxsize;
    L.incrementsize=incresize;
}

void DestoryList(SqList &L)  //ɾ�����Ա�
{
    delete[] L.elem;
    L.listsize=0;
    L.length=0;
}

void ClearList(SqList &L)  //��ʼ�����Ա�
{
    int i = 1;
    char *p = L.elem;
    while(i <= L.length)
    {
        *p++=NULL;
        ++i;
    }
    L.listsize=0;
    L.length=0;
}

bool ListEmpty(SqList L)  //�ж����Ա�L�Ƿ�Ϊ��
{
    if(L.length==0)
        return true;
    else
        return false;
}

int ListLength(SqList L)  //�ж����Ա�L����
{
    return L.length;
}

char GetElem(SqList L,int i,char e) //ȡ��Ԫ��
{
	if(i<1||i>L.length)
        cout << "�޵�" << i << "����" <<endl;
    char *p = L.elem;
	e = *(p+i-1);
    return e;
}

int LocateElem(SqList L,char e) //ȷ��λ��
{
    int i = 1;
    char *p = L.elem;
    while(i <= L.length && *p++ != e)
        ++i;
    if(i <= L.length)
        return i;
    else return 0;
}

char PriorElem(SqList L,char cur_e,char pre_e)  //Ѱ��ǰһ��Ԫ��
{
    char *p = L.elem;
    int i = 1;
    while(i <= L.length && *p++ != cur_e)
		++i;
    if(i <= L.length)
        pre_e = *(p-2);
    else 
		pre_e = NULL;
	if(LocateElem(L,(*(p-1))) == 1)
		pre_e = NULL;
	return pre_e;
}

char NextElem(SqList L,char cur_e,char next_e) //Ѱ����һ��Ԫ��
{
    int *p = L.elem;
    int i = 1;
	while(i <= L.length && *p++ != cur_e)
		++i;
    if(i <= L.length)
        next_e = *(p);
    else 
		next_e = NULL;
	if(LocateElem(L,(*(p-1))) == L.length)
		next_e = NULL;
    return next_e;
}

void increment(SqList &L) 
{
    int *a;
    a=new int[L.listsize+L.incrementsize];
    for(int i=0;i<L.length;i++)
        a[i]=L.elem[i];
    delete[] L.elem;
    L.elem=a;
    L.listsize += L.incrementsize;
}

void ListInsert(SqList &L,int i,int e) //����
{
	int *p;
	int *q;
    if(i<1||i>L.length+1)
        cout << "iֵ���Ϸ�" <<endl;
    if(L.length>=L.listsize)
        increment(L);
    q=&(L.elem[i-1]);
    for (p=&(L.elem[L.length-1]);p>=q;p--)
        *(p+1)=*p;
    *q=e;
    ++L.length;
}

int ListDelete(SqList &L,int i)//ɾ��һ��Ԫ��
{
	int *p;
	p = &(L.elem[i-1]);
	int *q;
	q = L.elem+L.length-1;

    if(i<1||i>L.length+1)
        cout << "iֵ���Ϸ�" <<endl;
    int e=*p;
    for(++p;p<=q;++p)
		*(p-1)=*p;
    --L.length;
	return e;
}

void ListTraverse(SqList L)
{
	int i = 0;
	cout << "����Ϊ:";
	while(i < L.length)
	{
		cout << L.elem[i] << "  ";
		i++;
	}
	cout << endl;
}

SqList Union(SqList &La,SqList &Lb,SqList &Lc)//��
{
	int La_len=ListLength(La);
	int e;
	for(int i=1;i<=La_len;i++)
		ListInsert(Lc,i,La.elem[i-1]);
	int Lc_len=ListLength(Lc);
	int b = Lb.length;
	while(b--)
	{
		e = GetElem(Lb,b+1,e);
		if(LocateElem(Lc,e) == 0)
			ListInsert(Lc,++Lc_len,e);
	}
	return Lc; 
}

SqList jiao(SqList &La,SqList &Lb,SqList &Lc)//��
{
	int La_len=ListLength(La);
	int e;
	int Lb_len=ListLength(Lb);
	int Lc_len=ListLength(Lc);
	while(Lb_len--)
	{
		e = GetElem(Lb,Lb_len+1,e);
		if(LocateElem(La,e) != 0)
			ListInsert(Lc,++Lc_len,e);
	}
	return Lc; 
}

SqList jian(SqList &La,SqList &Lb,SqList &Lc)//��
{
	int La_len=ListLength(La);
	int e;
	int k;
	for(int i=1;i<=La_len;i++)
		ListInsert(Lc,i,La.elem[i-1]);
	int Lb_len=ListLength(Lb);
	int Lc_len=ListLength(Lc);
	while(Lb_len--)
	{
		e = GetElem(Lb,Lb_len+1,e);
		k = LocateElem(La,e);
		if(k != 0)
			ListDelete(Lc,LocateElem(La,e));

	}
	return Lc; 
}


int main()
{
	SqList La,Lb,Lc;
	int a,b,e,k;
	cout << "�����һ������Ԫ�ظ���";
	cin >> a;

	InitList(La);
	
	k = 1;
	cout << "������Ԫ�ص�ֵ";
	while(k<=a)
	{
		
		cin >> e;
		ListInsert(La,k,e);
		k++;
	}

	cout << "����ڶ�������Ԫ�ظ���";
	cin >> b;
	InitList(Lb);
	k = 1;		
	cout << "������Ԫ�ص�ֵ";
	while(k<=b)
	{

		cin >> e;
		ListInsert(Lb,k,e);
		k++;
	}
	InitList(Lc);

	cout << "A";
	ListTraverse(La);

	cout << "B";
	ListTraverse(Lb);
	
	Union(La,Lb,Lc);
	cout << "A��B:\n";
	ListTraverse(Lc);

	ClearList(Lc);
	
	jiao(La,Lb,Lc);
	cout << "A��B:\n";
	ListTraverse(Lc);

	ClearList(Lc);

	jian(La,Lb,Lc);
	cout << "A��B:\n";
	ListTraverse(Lc);

	ClearList(Lc);

	jian(Lb,La,Lc);
	cout << "B��A:\n";
	ListTraverse(Lc);
}