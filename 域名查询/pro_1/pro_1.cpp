// pro_1.cpp : Defines the entry point for the console application.
//”Ú√˚≤È’“

//#include "stdafx.h"
#include <iostream>
#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include <windows.h>
#include <conio.h>

using namespace std;

typedef struct CSNode
{
    char Name[50];
    char ip[20];
    struct CSNode *firstchild, *nextsibling;

}CSNode, *CSTree;


typedef struct Pointer
{
    CSNode * point[30];
    int last;

}Pointer;

CSTree T;
Pointer P;

void WriteToFile(CSTree T, FILE *fp);
void ReadFromFile(CSTree &T, FILE *fp);
void CreateTree(CSTree &T);
void SearchTree(CSTree T);


void CreateTree(CSTree &T)
{
    char Name[50] = {'\0'};
    char ip[20];

    while(1)
    {
        memset(P.point,'\0',sizeof(P));
        cout<<"put in the domain name:";
        cin>>Name;
		cout<<endl;
        cout<<"put in IP:";
        cin>>ip;

        int i = 0, j = 0, k = 0;
        char transient[20] = {'\0'};

        while(Name[i] != '\0')
        {
            transient[j++] = Name[i++];
            if(Name[i] == '.' || Name[i] == '\0')
            {
                CSNode *p = new CSNode;
                strcpy(p->Name, transient);
                strcpy(p->ip,"NULL");
                p->firstchild = p->nextsibling = NULL;

                P.point[k] = p;
                P.last = k;
                k++;

                for(int m = 0; m<20; m++)
                    transient[m] = '\0';
                j = 0;
                i++;
            }
        }

        CSNode *t = T, *q;
        while( P.last >= 0 )
        {
            CSNode *p = P.point[P.last];

            if( (t->firstchild) == NULL)
            {
                t->firstchild = p;
                t = p;
            }
            else
            {
                t = t->firstchild;
                while(t != NULL && strcmp(t->Name , p->Name) != 0)
                {
                    q = t;
                    t = t->nextsibling;
                }
                if( t==NULL )
                {
                    q->nextsibling = p;
                    t =  p;
                }
            }
            P.last--;
        }
        strcpy(t->ip, ip);
    }

    FILE *fp = fopen("Name.txt", "w");
    WriteToFile(T->firstchild, fp);
    fclose(fp);
}

void SearchTree(CSTree T)
{
    char Name[50] = {'\0'};

    FILE *fp = fopen("Name.txt","r");
    ReadFromFile(T->firstchild,fp);
    fclose(fp);

    while(1)
    {
        memset(P.point,'\0',sizeof(P));
        cout<<"put in the domain name: ";
        cin>>Name;
        int i = 0, j = 0, k = 0;
        char transient[20] = {'\0'};

        while(Name[i] != '\0')
        {
            transient[j++] = Name[i++];
            if(Name[i] == '.' || Name[i] == '\0')
            {
                CSNode *p = new CSNode;
                strcpy(p->Name, transient);
                strcpy(p->ip,"NULL");
                p->firstchild = p->nextsibling = NULL;

                P.point[k] = p;
                P.last = k;
                k++;

                for(int m = 0; m<20; m++)
                    transient[m] = '\0';
                j = 0;
                i++;
            }
        }

        CSNode *t = T;
        while( P.last >= 0 )
        {
            CSNode *p = P.point[P.last];
            t = t->firstchild;
            if( !t && strcmp(t->Name, p->Name) != 0)
                t = t->nextsibling;
            if(t == NULL)
            {
                cout<<"DNS wrong !"<<endl;
                break;
            }
            P.last--;
        }
        if(t != NULL)
            cout<<"\nThe IP is: "<<t->ip<<endl;

        cout<<"\nPress any key to continue... "<<endl;
        getch();
    }
}

void WriteToFile( CSTree T, FILE *fp)
{
    char Ltag = '0', Rtag = '0';
    if(T)
    {
        fputs(T->Name,fp);
        fputs("\t",fp);
        fputs(T->ip,fp);
        fputs("\t",fp);
        if(T->firstchild != NULL)
        {
            Ltag = '1';
        }
        fwrite(&Ltag, sizeof(char), 1, fp);
        fputs("\t",fp);

        if(T->nextsibling != NULL)
        {
            Rtag = '1';
        }
        fwrite(&Rtag, sizeof(char), 1, fp);
        fputs("\n",fp);

        WriteToFile(T->firstchild, fp);
        WriteToFile(T->nextsibling, fp);
    }
}

void ReadFromFile( CSTree &T, FILE *fp)
{
    CSTree p;
    char LG='0',RG='0';
    p = new CSNode;
    p->firstchild = p->nextsibling = NULL;
    fscanf(fp,"%s\t%s\t%c\t%c",p->Name,p->ip,&LG,&RG);//&LG?
    T = p;
    if(LG=='1')
    ReadFromFile(T->firstchild,fp);
    if(RG=='1')
    ReadFromFile(T->nextsibling,fp);
}


void Menu()
{
    system("cls");
    cout<<"\n\n"
        <<"\t\t~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~\n"
        <<"\t\t*                                                      *\n"
        <<"\t\t*      [1] Original domain name information input      *\n"
        <<"\t\t*                                                      *\n"
        <<"\t\t*      [2] Internet domain name searching              *\n"
        <<"\t\t*                                                      *\n"
        <<"\t\t*      [3] exit                                        *\n"
        <<"\t\t*                                                      *\n"
        <<"\t\t~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~\n"
        <<endl;
}
int main()
{
	int n;
    T = new CSNode;
    T->firstchild = T->nextsibling = NULL;
    while(1)
    {
        Menu();
        cin>>n;
        switch(n)
        {
            case 1:
                {
                    CreateTree(T);
                    break;
                }
            case 2:
                {
                    SearchTree(T);
                     break;
                }
            case 3:
                {
                    exit(0);
                }
        }
    }

	
	return 0;
}

