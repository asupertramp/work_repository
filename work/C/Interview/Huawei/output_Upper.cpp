#include<iostream>
#include<string>
#include<cstdlib>
using namespace std;
int main()
{
	string s,tmp;
	char comma;
	int n;
	cin>>n>>comma>>s;
	while(s.size()<n)
	{
		cin>>tmp;
		s+=tmp;
	}
	if(s.size()>n)
		s=s.substr(0,n);
	for(size_t i=0;i<s.size();++i)
		if(s[i]>='A'&&s[i]<='Z')
			cout<<s[i];
	system("pause");	
	return 0;
}