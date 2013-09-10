#include<stdio.h>
int fib1(int n)
{
	if(n==1||n==2)
		return 1;
	return fib1(n-1)+fib1(n-2);
}
int fibTailRecursive(int n,int acc1,int acc2)
{
	if(n==0)
		return acc1;
	else
		return fibTailRecursive(n-1,acc2,acc1+acc2);
}
int main()
{
	int n;
	while(1)
	{
		scanf("%d",&n);
		printf("%d\n",fibTailRecursive(n,0,1));
		printf("%d\n",fib1(n));
		
	}
	return 0;
	
}