#include<iostream>
#include<cstdlib>
using namespace std;
int main()
{
	int face[]={100,50,10,5,1};
	int money;
	cin>>money;
	if(money<0)
	{
		cout<<"不能为负！"<<endl;
		return 0;
	}
	int i=0,count=0;
	while(money)
	{
		count+=money/face[i];
		money=money%face[i++];
	}
	cout<<count<<endl;
	system("PAUSE");
	return 0;
}