#include<stdio.h>
void bubble(int *arr,int n)
{
	int i,j,tmp;
	for(i=0;i<n;++i)
	{
		for(j=n-1;j>i;--j)
		{
			if(arr[j]<arr[j-1])
			{
				tmp=arr[j];
				arr[j]=arr[j-1];
				arr[j-1]=tmp;
			}
		}
	}
}
int main()
{
	int i;
	int arr[]={10,9,8,7,6,5,4,3,2,1};
	bubble(arr,10);
	for(i=0;i<10;++i)
		printf("%d£¬",arr[i]);
	return 0;
}