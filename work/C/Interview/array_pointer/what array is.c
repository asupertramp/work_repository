#include<stdio.h>
void func(int *p)
{
	printf("the length of p %d\n",sizeof(p));//output:4
}
void func2(int p[])//��������Ϊ�β�ʱ���ƺ��൱��ָ��
{
	printf("the length of p %d\n",sizeof(p));//output:4
}
int main()
{
	int arr[10]={1,2,3,4,5,6,7,8,9,0};
	int *p1=arr;//��������ƥ�����arr������Ӧ����int*
	//int (*p2)[10]=arr;//warning
	int (*p2)[10]=&arr;//p2��һ��ָ�룬ָ��һ������10��int��Ԫ�ص�����
						//�˴�arr�����ͺ���Ӧ���ǡ�һ������10��int��Ԫ�ص����顱
	printf("*p2:%d \n",*p2);//����ͨ������������Ӧ����������׵�ַ
	printf("**p2:%d\n",**p2);//���arr[0]
	//int **p3=&arr;//error
	int *p4[]={arr};//p4��һ�����飬���int*�͵�Ԫ��
	printf("**p4:%d\n",**p4);
	
	
	int arr_len=sizeof(arr);
	printf("the length of arr:%d\n",arr_len);//output:40
	arr_len=sizeof(p1);
	printf("the length of arr:%d\n",arr_len);//output:4
	
	func(arr);
	func2(arr);
	return 1;
}