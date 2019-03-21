#include <iostream>

using namespace std;

struct duoxiangshi{
    int ex;   //次数
    int co;   //系数
}dxs[1001];

int main(){
    int a,b,A[2005]={0},B[1005]={0};

	int i,j;

    cin >> a;

    int temp1,temp2;

	int flag1 = 1, flag2 = 0;

    for(i = 0; i < a; i++)
	{
		cin >> dxs[i].co >> dxs[i].ex;  //先输入系数，后输入指数
        B[dxs[i].ex] += dxs[i].co;      //指数作为下标，系数作为数组元素
    }

    cin >> b;

    for(i = 0; i < b; i++)
	{
		cin >> temp1 >> temp2;
        B[temp2] += temp1;        
        
		for(j = 0; j < a; j++)
            A[temp2+dxs[j].ex]+=(temp1*dxs[j].co);  //指数相加，系数相乘
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
				cout << A[i] << " " << i;    //判断是不是第一个输出，第一个输出少一个空格
            }
            flag2 = 1;   //如果执行了if语句则不是零多项式
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