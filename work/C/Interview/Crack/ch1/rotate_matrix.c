/*将一个方阵旋转90度。第一步交换主对角线两测的元素，第二步交换第i和第n-1-i行*/
#include<stdio.h>
void swap_line(int a[],int b[],int n);
void rotate_matrix(int a[][3],int n)
{
	int i ,j,temp;
	for(i=0;i<n;++i)
		for(j=i+1;j<n;++j)
		{
			temp=a[i][j];
			a[i][j]=a[j][i];
			a[j][i]=temp;
		}
	for(i=0;i<n/2;++i)
		swap_line(a[i],a[n-i-1],n);
}
void swap_line(int a[],int b[],int n)
{
	int i,temp;
	for(i=0;i<n;++i)
	{
		temp=a[i];
		a[i]=b[i];
		b[i]=temp;
	}
}
void printArr(int a[][3],int n)
{
	int i,j;
	for(i=0;i<n;++i)
	{
		for(j=0;j<n;++j)
			printf("%2d ",a[i][j]);
		printf("\n");
	}
}

int main()
{
	int arr[3][3]={1,2,3,4,5,6,7,8,9};
	printArr(arr,3);
	rotate_matrix(arr,3);
	printArr(arr,3);
}