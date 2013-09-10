#include<stdio.h>
void func(int a)
{
	printf("%d\n",a);
}
void  func(char a)
{
	printf("%c",a);
}
int main()
{
	func(1);
	func('a');
}
