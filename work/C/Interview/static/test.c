//关于static:static首先在C中引入，表示退出一个块后依然存在的局部变量，随后，static在C中有了第二种含义，表示不能被其他文件访问的全局变量和函数；C++第三次重用了这///个关键字，属于类而不属于对象的变量或函数，这个含义与java中相同。
#include<stdio.h>
void fun()
{
	static int i=0;
	printf("%d  ",++i);
}
int main()
{
	fun();
	fun();
	fun();
	fun();
	return 0;
}