#include<stdio.h>
#include<stdlib.h>
int main()
{
	printf("call abort()\n");
	abort();
	printf("this is never reached");
	return 0;
}