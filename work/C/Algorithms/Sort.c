#include<stdio.h>
#include<limits.h>
#include<stdlib.h>

void Insertion(int arr[],int n)
{
	int i,j,tmp;
	for(i=1;i<n;++i)
	{
		tmp=arr[i];
		for(j=i;j>0&&tmp<arr[j-1];--j)
				arr[j]=arr[j-1];
		arr[j]=tmp;
	}
}



void Merge(int a[],int left,int center,int right)
{
	int *tmpl,*tmpr,i,j,k;
	if((tmpl=(int *)malloc(sizeof(int)*(center-left+2)))==NULL||
		(tmpr=(int *)malloc(sizeof(int)*(right-center+1)))==NULL)
		exit(1);
	for(i=0;i<center-left+1;++i)
		*(tmpl+i)=a[left+i];
	tmpl[center-left+1]=INT_MAX;
	for(i=0;i<right-center;++i)
		*(tmpr+i)=a[center+1+i];
	tmpr[right-center]=INT_MAX;
	for(i=0,j=0,k=0;i<right-left+1;++i)
	{
		if(*(tmpl+j)<*(tmpr+k))
			a[left+i]=tmpl[j++];
		else
			a[left+i]=tmpr[k++];
	}
	free(tmpl);
	free(tmpr);
}
void MergeSort(int arr[],int l,int r)
{
	int c;
	if(l>=r)
		return;
	c=(l+r)/2;
	MergeSort(arr,l,c);
	MergeSort(arr,c+1,r);
	Merge(arr,l,c,r);
}


void Bubbling(int a[],int n)
{
	int i,j,tmp;
	for(i=1;i<n;++i)
	{
		tmp=a[i];
		for(j=i;j>0&&a[j-1]>tmp;--j)
			a[j]=a[j-1];
		a[j]=tmp;
	}
}


int partition(int a[],int l,int r)
{
	int i,j,tmp;
	if(l>=r)
		return;
	for(i=l,j=l-1;i<r;++i)
	{
		if(a[i]<a[r])
		{
			j++;
			tmp=a[j];
			a[j]=a[i];
			a[i]=tmp;
		}	
	}
	tmp=a[j+1];
	a[j+1]=a[r];
	a[r]=tmp;
	return j+1;
}
void QuickSort(int a[],int l,int r)
{
	int p;
	if(l>=r)
		return;
	p=partition(a,l,r);
	QuickSort(a,l,p-1);
	QuickSort(a,p+1,r);
}



void KeepHeap(int a[],int p,int n)
{
	int largest,left,right,tmp;
	left=2*p+1;
	right=2*p+2;
	largest=p;
	if(left<n&&a[largest]<a[left])
		largest=left;
	if(right<n&&a[largest]<a[right])
		largest=right;
	if(largest!=p)
	{
		tmp=a[p];
		a[p]=a[largest];
		a[largest]=tmp;
		KeepHeap(a,largest,n);
	}
}
void BuildHeap(int a[],int n)
{
	int i;
	for(i=n/2-1;i>=0;--i)
		KeepHeap(a,i,n);
}
void HeapSort(int a[],int n)
{
	int tmp,i;
	BuildHeap(a,n);
	for(i=n-1;i>=0;--i)
	{
		tmp=a[0];
		a[0]=a[i];
		a[i]=tmp;
		KeepHeap(a,0,i);
	}
}


void ShellSort(int a[],int n)
{
	int gap,i,j,tmp;
	for(gap=n/2;gap>0;gap/=2)//‘ˆ¡øµ›ºı
		for(i=gap;i<n;++i)	
			for(j=i-gap;j>=0&&a[j]>a[j+gap];j-=gap)//≤Â»Î≈≈–Ú
			{
				tmp=a[j];
				a[j]=a[j+gap];
				a[j+gap]=tmp;
			}
}


void print_array(int arr[],int n)
{
	int i;
	for(i=0;i<n;++i)
		printf("%d ",arr[i]);
	printf("\n");
}
void test()
{
	int arr[]={9,8,7,6,5,4,3,2,1};
	int a2[]={1,2,3,4,5,6,7,8,9};
	//Insertion(arr,sizeof(arr)/sizeof(int));
	//Merge(arr,0,2,5);
	//MergeSort(arr,0,sizeof(arr)/sizeof(int)-1);
	//Bubbling(arr,sizeof(arr)/sizeof(int));
	//QuickSort(arr,0,8);
	//BuildHeap(a2,9);
	//HeapSort(arr,9);
	ShellSort(arr,9);
	print_array(arr,sizeof(arr)/sizeof(int));
}
int main()
{
	test();
}