#include<stdlib.h>
#include<stdio.h>

int main()
{
	float f;
	int i;
	long l;
	char *s="123456.7";
	printf("atof:%f\n",atof(s));
	printf("atoi:%d\n",atoi(s));
	printf("atol:%ld\n",atol(s));
	return 0;
}