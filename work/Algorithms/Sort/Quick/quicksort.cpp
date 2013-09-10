#include<iostream>
#include<vector>
using namespace std;
int partition(int *a,int p,int r);
int quicksort(int *a,int p,int len);
int main()
{
	cout<<"input numbers to sort:"<<endl;
	vector<int> ivec;
	int temp;
	while((cin>>temp)&&temp!=-1)
	{
		ivec.push_back(temp);
	}
	int *arr=new int[ivec.size()];
	for(vector<int>::size_type i=0;i!=ivec.size();++i)
		arr[i]=ivec[i];
	quicksort(arr,0,ivec.size());
	for(vector<int>::size_type i=0;i!=ivec.size();++i)
		cout<<arr[i]<<" ";
	return 0;	
}

int partition(int *a,int p,int r)
{
	int i=p-1;
	int j=p;
	int part=a[r-1];
	for(;j!=r-2;++j)
	{
		if(a[j]<=part)
		{
			i++;
			int temp=a[i];
			a[i]=a[j];
			a[j]=temp;
		}
	}
	int temp=a[r-1];
	a[r-1]=a[i+1];
	a[i+1]=temp;
	return i+1;
}

int quicksort(int *a,int p,int len)
{
	int q=partition(a,p,len);
	quicksort(a,p,q-1);
	quicksort(a,q+1,len);
	
}