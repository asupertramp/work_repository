/**/
#include<stdio.h>
int find1(int arr[],int len)
{
	int i,temp=0;
	for(i=0;i<len;++i)
		temp^=arr[i];
	return temp;
}

int find_first1bit(int a)
{
	int i;
	for(i=0;a!=0;++i)
	{
		if(a&1==1)
			return i;
		a>>=1;
	}
	return i;
}
void find2(int arr[] ,int *a,int *b ,int len)
{
	int i,j,sum=0,a1=0,b1=0;
	for(i=0;i<len;++i)
		sum^=arr[i];
	j=find_first1bit(sum);
	for(i=0;i<len;++i)
	{
		if(((arr[i]>>j)&1)==0)
			a1^=arr[i];
		else
			b1^=arr[i];
	}
	*a=a1;
	*b=b1;
}
void find3()
int main()
{
	int arr1[]={1,1,2,2,3,3,4,4,5,6,6,7,7};
	int arr2[]={1,1,2,2,3,4,5,5,6,6};
	int a,b;
	printf("find1:%d\n",find1(arr1,sizeof(arr1)/sizeof(int)));
	find2(arr2,&a,&b,sizeof(arr2)/sizeof(int));
	printf("find2:%d,%d\n",a,b);
	printf("find_first1bit(5):%d\n",find_first1bit(5));
	return 0;
}