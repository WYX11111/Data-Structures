#include "Stack.cpp"
#include "Queue.cpp"
#include <stdio.h>
#include <stdlib.h>
#include <conio.h>
#include <ctype.h>

void main()
{
	SqQueue sidewalk;
	SqStack garage,garagebuf;

	InitStack_Sq(garage);
	InitStack_Sq(garagebuf);
	InitQueue_Sq(sidewalk);

	char order;
	int e;
	int k;

	while(1)
	{
		StackTraverse(garage);
		QueueTraverse(sidewalk);

		printf("=====Input your order folloe the instruction bellow=====\n");
		printf("     ( Garage capacity: %d,   sidewalk capacity: %d )\n",STACK_INIT_SIZE,QUEUE_INIT_SIZE-1);
		printf("     I: In\n");
		printf("     O: Out\n");
		printf("     X: Exit\n");
		printf("����ָ��: ");
		order = getche();
		printf("\n");
		switch(toupper(order))
		{
		case 'I': 
			{
				if(QueueFull_Sq(sidewalk))
					printf("����\n");
				else
				{
					printf("���복��: ");
					scanf("%d",&e);
					
					if(StackFull_Sq(garage))
					{
						if(ElemInQueue(sidewalk, e))
							printf("������ͬ���ţ���ȷ�ϳ���\n");
						else
							EnQueue_Sq(sidewalk, e);
					}
					else
					{
						if(ElemInStack(garage, e))
							printf("������ͬ���ţ���ȷ�ϳ���\n");
						else
							Push_Sq(garage, e);
					}
				}
			}break;
		case 'O':
			{
				if(StackEmpty_Sq(garage))
					printf("û�г�\n");
				else
				{
					printf("���복��: ");
					scanf("%d",&e);
					
					if(ElemInStack(garage, e))
					{
						while(ElemInStack(garage, e))
						{
							Pop_Sq(garage, k);
							Push_Sq(garagebuf, k);
						}
						Pop_Sq(garagebuf, k);
						while(!StackEmpty_Sq(garagebuf))
						{
							Pop_Sq(garagebuf, k);
							Push_Sq(garage, k);
						}
						if(!QueueEmpty_Sq(sidewalk))
						{
							DeQueue_Sq(sidewalk, e);
							Push_Sq(garage, e);
						}
					}
					else
					{
						printf("�ó����ڳ����У���ȷ�ϳ���\n");
					}
				}
			}break;
		case 'X':exit(0);break;
		}
	}
}