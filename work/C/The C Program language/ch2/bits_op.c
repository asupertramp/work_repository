#include<stdio.h>

int wordLen();
int  rightrot(int x,int n)
{
	int wordLength=wordLen();
	int temp;
	if(n%wordLength!=0)
	{
		temp=(~(~0<<n)&x)<<(wordLength-n);
		return (x>>n)|temp;
	}
	return x;
}
//ͳ��x�ж�����λΪ1�ĸ���
int bitcount(unsigned x)
{
	int i;
	if(x==0)
		return 0;
	i=1;
	while((x&=(x-1))!=0)		//x&(x-1)����x���λ��1
		i++;
	return i;
}

int wordLen()
{
	int i;
	unsigned v=~0;
	for(i=1;(v>>=1)>0;++i)
		;
	return i;
}
int main()
{
	int x,n;
	printf("input x:");
	scanf("%d",&x);
	printf("input n:");
	scanf("%d",&n);
	printf("x<<n:%d\n",rightrot(x,n));
	printf("the bitcount of x:%d\n",bitcount(x));
}