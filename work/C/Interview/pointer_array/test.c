#include<stdio.h>
#include"ext.c"
extern int a[];
extern int *b;
int main()
{
	int x,y;
	x=a[3];
	y=b[3];
	printf("x:%d,y:%d",x,y);
	return 0;
}