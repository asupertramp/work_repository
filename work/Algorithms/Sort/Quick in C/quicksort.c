#include<stdio.h>

int partition(int arr[],int beg,int end);
void quicksort(int arr[],int beg,int end);
int main()
{
	int i=0,j,arr[100]={9,8,7,6,5,4,3,2,1,0};
	// // printf("please input numbers to sort:\n");
	// // while(scanf("%d",&arr[i++]))
		//;
	i=10;
	quicksort(arr,1,i-1);
	for(j=0;j<i;j++)
		printf("%d,",arr[j]);
}

int partition(int arr[],int beg,int end)
{
	int j,temp, middle=arr[end];
	int ret=beg-1;
	for(j=beg;j<end;j++)
	{
		if(arr[j]<middle)
		{
			ret++;
			temp=arr[ret];
			arr[ret]=arr[j];
			arr[j]=temp;
		}
	}
	arr[end]=arr[ret+1];
	arr[ret+1]=middle;
	return ret+1;
}

void quicksort(int arr[],int beg,int end)
{
	int middle=partition(arr,beg,end);
	quicksort(arr,beg,middle-1);
	quicksort(arr,middle+1,end);
}