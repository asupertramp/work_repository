#include<iostream>
#include<stack>
#include<string>
using namespace std;
int priority(char opera)
{
	int p;
	switch(opera)
	{
		case '+':
		case '-':
			p=0;
			break;
		case '*':
		case '/':
			p=1;
			break;
		case '(':
			p=-1;
			break;
		case ')':
			p=2;
			break;
	}
	return p;
}
void infix_to_postfix(const string &in,string &out)
{
	stack<char> s;
	size_t  i,j=0;
	for( i=0;i<in.size();++i)
	{
		char c=in[i];
		if(c>='0'&&c<='9')
			out[j++]=c;
		else
		{
			int p=priority(c);
			if(p==2)
			{
				while(s.top()!='(')
				{
					out[j++]=s.top();
					s.pop();
				}
				s.pop();
			}
			else
			{
				while(priority(s.top())>p&&!s.empty())
				{
					out[j++]=s.top();
					s.pop();
				}
				s.push(c);
			}		
		}
	}
	while(!s.empty())
	{
		out[j++]=s.top();
		s.pop();
	}
	//out[j]='\0';
}
int main()
{
	string s1="1+2*4-5/6";
	string s2="a";
	s2.resize(20);
	infix_to_postfix(s1,s2);
	cout<<s2<<endl;
	return 0;
}
