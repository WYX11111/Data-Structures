// ���������� + ����ַ����
#include<stdio.h>
#include<stdlib.h>

typedef int BOOL;
#define FALSE 0
#define TRUE 1

//�����ϣ��ͻ������ݽڵ�
typedef struct _NODE
{
    int data;
    struct _NODE* next;
}NODE;

typedef struct _HASH_TABLE
{
    NODE* value[10];
}HASH_TABLE;

//������ϣ��
HASH_TABLE* create()
{
    HASH_TABLE* Hash = new HASH_TABLE;
    for (int i = 0; i < 10; i++)
		Hash->value[i] = NULL;
    return Hash;
}

//�ڹ�ϣ���в�������
NODE* find(HASH_TABLE* Hash, int data)
{
    NODE* pNode;
    if(Hash == NULL)
        return NULL;

	pNode = Hash->value[data % 10];
    
	if(pNode == NULL)
        return NULL;

    while(pNode)
	{
        if(pNode->data == data)
            return pNode;
        pNode = pNode->next;
    }
    return NULL;
}

//�ڹ�ϣ���в�������
BOOL insert(HASH_TABLE* Hash, int data)
{
    NODE* pNode;
    if(Hash == NULL)
        return FALSE;

    if(Hash->value[data % 10] == NULL)
	{
        pNode = new NODE;
        pNode->next = NULL;
        pNode->data = data;
        Hash->value[data % 10] = pNode;
        return TRUE;
    }

    if(find(Hash, data) != NULL)
        return FALSE;

    pNode = Hash->value[data % 10];

    while(pNode->next != NULL)
        pNode = pNode->next;

    pNode->next = new NODE;
    pNode->next->next = NULL;
    pNode->next->data = data;
    return TRUE;
}

//�ӹ�ϣ����ɾ������
BOOL del(HASH_TABLE* Hash, int data)
{
    NODE* pHead;
    NODE* pNode;
    if(Hash == NULL || Hash->value[data % 10] == NULL)
        return FALSE;
	pNode = find(Hash, data);
    
	if(pNode == NULL)
        return FALSE;

    if(pNode == Hash->value[data % 10])
	{
        Hash->value[data % 10] = pNode->next;
        delete pNode;
        return TRUE;
    }

    pHead = Hash->value[data % 10];

    while(pNode != pHead->next)
        pHead = pHead->next;
    pHead->next = pNode->next;
}

 void main()
{
    HASH_TABLE* hashtable = create();   //������ϣ��
    
	insert(hashtable,1);
    insert(hashtable,4);
    insert(hashtable,11);
    insert(hashtable,21);               //�����������

    NODE* node1=find(hashtable,1);
    NODE* node2=find(hashtable,4);
	NODE* node3=find(hashtable,11);
	NODE* node4=find(hashtable,21);

	printf("hashtable 1 : %d \n",node1->data);
	printf("hashtable 1 : %d \n",node2->data);
    printf("hashtable 1 : %d \n",node3->data);
    printf("hashtable 1 : %d \n",node4->data);

    del(hashtable,21);                  //ɾ������
    
	NODE* node5=find(hashtable,21);

    if(node5==NULL) 
		printf("21 is cancel\n");
	else 
		printf("hashtable 1 : %d \n",node5->data);
}