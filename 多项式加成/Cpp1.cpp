#include <iostream>

using namespace std;

struct duoxiangshi{
    int ex;   //����
    int co;   //ϵ��
}dxs[1001];

int main(){
    int a,b,A[2005]={0},B[1005]={0};

	int i,j;

    cin >> a;

    int temp1,temp2;

	int flag1 = 1, flag2 = 0;

    for(i = 0; i < a; i++)
	{
		cin >> dxs[i].co >> dxs[i].ex;  //������ϵ����������ָ��
        B[dxs[i].ex] += dxs[i].co;      //ָ����Ϊ�±꣬ϵ����Ϊ����Ԫ��
    }

    cin >> b;

    for(i = 0; i < b; i++)
	{
		cin >> temp1 >> temp2;
        B[temp2] += temp1;        
        
		for(j = 0; j < a; j++)
            A[temp2+dxs[j].ex]+=(temp1*dxs[j].co);  //ָ����ӣ�ϵ�����
    }

    for(i = 2000; i >= 0; i--)
	{
        if(A[i] != 0)
		{
            if(!flag1)
				cout << " " <<A[i] << " " << i;
            if(flag1)
			{
                flag1 = 0;
				cout << A[i] << " " << i;    //�ж��ǲ��ǵ�һ���������һ�������һ���ո�
            }
            flag2 = 1;   //���ִ����if������������ʽ
        }
    }

    if(!flag2)
		cout << "0 0";
    flag2 = 0;
    flag1 = 1;

    cout << endl;

    for(i = 1000; i >= 0; i--)
	{
        if(B[i] != 0){
            if(!flag1)
				cout << " " <<B[i] << " " << i;
            if(flag1)
			{
				cout <<	B[i] << " " << i;
                flag1 = 0;
            }
            flag2 = 1;   
        }
    }       
    if(!flag2) 
		cout << "0 0";
    return 0;
}