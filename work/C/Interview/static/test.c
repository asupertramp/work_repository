//����static:static������C�����룬��ʾ�˳�һ�������Ȼ���ڵľֲ����������static��C�����˵ڶ��ֺ��壬��ʾ���ܱ������ļ����ʵ�ȫ�ֱ����ͺ�����C++��������������///���ؼ��֣�������������ڶ���ı������������������java����ͬ��
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