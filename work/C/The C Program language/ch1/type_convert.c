
//��unsigned������signed���ͱȽϴ�Сʱ���ȽϽ��ȡ���ڻ����и����͵Ĵ�С
//����ͬ���ݳ��ȵ�unsigned��signed�Ƚ�ʱ��signed��ת��unsigned
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