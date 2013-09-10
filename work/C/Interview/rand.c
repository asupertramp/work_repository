#include<stdio.h>
#include<stdlib.h>
#include<time.h>
void shuffle(int *deck,int n)
{
	int i;
	static int first=1;
	if(first)
	{
		first=0;
		srand((unsigned int)time(NULL));
	}
	
	for(i=n-1;i>0;--i)
	{
		int where,temp;
		where=rand()%i;
		temp=deck[where];
		deck[where]=deck[i];
		deck[i]=temp;
	}
}
void print(int *deck,int n)
{
	int i;
	for(i=0;i<n;++i)
		printf("%d ",deck[i]);
	printf("\n");
}
int main()
{
	int deck[]={1,2,3,4,5,6,7,8,9,10};
	int c;
	while(c=getchar())
	{
		shuffle(deck,10);
		print(deck,10);
	}
}