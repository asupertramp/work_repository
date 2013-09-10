#include<stdio.h>
void shell(int *arr,int n)
{
	int d=n;
	int i,tmp;
	while(d>1)
	{
		d=(d+1)/2;
		for(i=0;i<n-d;++i)
			if(arr[i]>arr[i+d])
			{
				tmp=arr[i];
				arr[i]=arr[i+d];
				arr[i+d]=tmp;
			}
	}
}
int main()
{
	int arr[]={10,9,8,7,6,5,4,3,2,1};
	int i;
	shell(arr,10);
	for(i=0;i<10;++i)
		printf("%d,",arr[i]);
	return 0;
}