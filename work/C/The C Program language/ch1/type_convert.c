
//当unsigned类型与signed类型比较大小时，比较结果取决于机器中各类型的大小
//当相同数据长度的unsigned和signed比较时，signed被转成unsigned
#include<stdio.h>
int main()
{
	if(-1L<1U)
		printf("-1L<1U\n");
	else
		printf("-1L>1U\n");
	if(-1L<1L)
		printf("-1L<1L\n");
	else
		printf("-1L>1L\n");
	if(-1<1U)
		printf("-1<1U\n");
	else
		printf("-1>1U\n");
	if(-1L<1UL)
		printf("-1L<1UL\n");
	else
		printf("-1L>1UL\n");
}