#include<stdio.h>
void print8(int n)
{
	if(n==0)
		return ;
	print8(n/8);
	printf("%d",n%8);
}
void print16(int  n)
{
	int tmp;
	if(n==0)
		return;
	print16(n/16);
	tmp=n%16;
	if(tmp>9)
	{
		printf("%c",'a'+tmp-10);
	}
	else
		printf("%d",tmp);
}
void print2(int n)
{
	if(n==0)
		return;
	print2(n/2);
	printf("%d",n%2);
}
int main()
{
	int n;
	while(1)
	{
		printf("input:\n");
		scanf("%d",&n);
		printf("8:");
		print8(n);
		printf("\n");
		
		printf("2:");
		print2(n);
		printf("\n");
		
		printf("16:");
		print16(n);
		printf("\n");
	}
	return 0;
}