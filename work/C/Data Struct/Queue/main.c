#include"queue.h"
#include"queue.c"
#include<stdio.h>
int main()
{
	int i;
	for(i=0;i<10;++i)
		qinsert(1);
	for(i=0;i<10;++i)
		printf("%d,",qdelete());
}