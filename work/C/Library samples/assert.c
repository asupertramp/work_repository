#include<assert.h>
#include<stdio.h>

int main()
{
	int i=1;
	printf("i=%d\n",i);
	assert(i>0);
	printf("assert(i>0)");
	return 0;
}