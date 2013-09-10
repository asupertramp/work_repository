#include"stack.h"
#include"stack.c"
#include<stdio.h>
int main()
{
	int i;
	for(i=0;i<10;++i)
		push(i);
	for(i=0;i<10;++i)
		printf("%d,",pop());
	return 0;
}