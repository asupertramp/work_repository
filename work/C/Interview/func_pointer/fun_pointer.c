#include<stdio.h>
void fun(void (*visit)(int))
{
	int arr[]={1,2,3,4,5};
	int i;
	for(i=0;i<sizeof(arr)/sizeof(int);++i)
		visit(arr[i]);
}
void print(int a)
{
	printf("%d " ,a);
}
int main()
{
	fun(print);
}
