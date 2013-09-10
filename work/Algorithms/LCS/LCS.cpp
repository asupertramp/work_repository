#include<iostream>
#include<string>
using namespace std;
enum dir{LEFT,UP,LEFT_UP};
void print_LCS(string x,int b[])
{
	
}
int main()
{
	string s1,s2;
	cin>>s1>>s2;
	int m=s1.size();
	int n=s2.size();
	int c[m+1][n+1];
	dir b[m][n];
	for(int i=0;i<=n;++i)
		c[0][i]=0;
	for(int j=0;j<=m;++j)
		c[j][0]=0;
	for(int i=0;i<m;++i)
		for(int j=0;j<n;++j)
		{
			if(s1[i]==s2[j])
			{
				c[i+1][j+1]=c[i][j]+1;
				b[i][j]=LEFT_UP;
			}
			else
			{
				if(c[i+1][j]>c[i][j+1])
				{
					c[i+1][j+1]=c[i+1][j];
					b[i][j]=LEFT;
				}				
				else
				{
					c[i+1][j+1]=c[i][j+1];
					b[i][j]=UP;
				}
			}
		}

}