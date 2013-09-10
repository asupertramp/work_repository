#include<stdio.h>
#include<io.h>

int main()
{
	printf("Dose access.c exist:");
	if(access("access.c",0)==0)
		printf("Yes\n");
	else
		printf("No\n");
	printf("access.c write permition:%d\n",access("access.c",2));
	return 0;
}