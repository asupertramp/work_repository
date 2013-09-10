#include<stdio.h>
void test()
{
	int i,val;
	char *c;
	val=0x1020304;
	printf("val:%x\n",val);
	c=(char*)&val;
	printf("c:%d\n",*c);
}
int main()
{
	test();
	return 0;
}
