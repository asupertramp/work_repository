#include<stdio.h>
#include<stdarg.h>
void func(int a,...)
{
	va_list ap;
	int sum=a;
	int p;
	va_start(ap,a);
	while((p=va_arg(ap,int))>0)
		sum+=p;
	va_end(ap);
	printf("%d\n",sum);
}
int main()
{
	func(1,2,3,4,5,6,7);
	func(1,2,3,4,-1);
	return 0;
}