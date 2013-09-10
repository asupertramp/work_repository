#include<stdio.h>
void func(int *p)
{
	printf("the length of p %d\n",sizeof(p));//output:4
}
void func2(int p[])//数组名作为形参时，似乎相当于指针
{
	printf("the length of p %d\n",sizeof(p));//output:4
}
int main()
{
	int arr[10]={1,2,3,4,5,6,7,8,9,0};
	int *p1=arr;//按照类型匹配规则，arr的类型应该是int*
	//int (*p2)[10]=arr;//warning
	int (*p2)[10]=&arr;//p2是一个指针，指向一个含有10个int型元素的数组
						//此处arr的类型好像应该是“一个含有10个int型元素的数组”
	printf("*p2:%d \n",*p2);//编译通过，但输出结果应该是数组的首地址
	printf("**p2:%d\n",**p2);//输出arr[0]
	//int **p3=&arr;//error
	int *p4[]={arr};//p4是一个数组，存放int*型的元素
	printf("**p4:%d\n",**p4);
	
	
	int arr_len=sizeof(arr);
	printf("the length of arr:%d\n",arr_len);//output:40
	arr_len=sizeof(p1);
	printf("the length of arr:%d\n",arr_len);//output:4
	
	func(arr);
	func2(arr);
	return 1;
}