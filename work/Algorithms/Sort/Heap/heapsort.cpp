#include<iostream>
#include<vector>
using namespace std;
void max_heapify(int *a,int i,int len);
void build_heap(int *a,int len);
void heap_sort(int *a,int len);

int main()
{
	cout<<"input numbers to sort:"<<endl;
	vector<int> ivec;
	int temp;
	while((cin>>temp)&&temp!=-1)
		ivec.push_back(temp);
	int *arr=new int[ivec.size()];
	for(int i=0;i<ivec.size();++i)
		arr[i]=ivec[i];
	heap_sort(arr,ivec.size());
	for(int i=0;i<ivec.size();++i)
		cout<<arr[i]<<" ";
	delete arr;
	return 1;
}

void max_heapify(int *a,int i,int len)
{
	int left=2*i;
	int right=2*i+1;
	int largest=i;
	if((left<len)&&a[i]<a[left])
		largest=left;
	if((right<len)&&(a[largest]<a[right]))
		largest=right;
	if(largest!=i)
	{
		int temp=a[i];
		a[i]=a[largest];
		a[largest]=temp;
		max_heapify(a,largest,len);
	}
}

void build_heap(int *a,int len) //T(n)=O(n)
{
	for(int i=len/2-1;i>=0;--i)
		max_heapify(a,i,len);
}

void heap_sort(int *a,int len)
{
	build_heap(a,len);
	for(int i=0;i<len;++i)
	{
		int temp=a[0];
		a[0]=a[len-i-1];
		a[len-i-1]=temp;
		max_heapify(a,0,len-i-1);
	}
}