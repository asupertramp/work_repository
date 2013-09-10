#include"queue.h"
#include"queue.c"
#include<stdio.h>
int main()
{
	int i;
	create_queue(-1);
	for(i=0;i<10;++i)
		qinsert(i);
	for(i=0;i<10;++i)
		printf("%d,",qdelete());
}