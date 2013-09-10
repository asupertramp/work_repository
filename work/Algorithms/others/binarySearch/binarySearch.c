#include<stdio.h>
#include<stdlib.h>
int main(){
	int arr[]={1,2,3,4,5,6,7,8,9,10};
	int i,j,p;
	while(1){
		for(i=0;i<10;i++){
			printf("%d ",arr[i]);
		}
		printf("\n");
		printf("input the number to find\n");
		scanf("%d",&j);
		p=binarySearch(arr,j,10);
		printf("%d \n",p);
	}
}

int binarySearch(int arr[],int val,int length){
	int low=0;
	int high=length-1;
	int mid;
	while(low<=high){
		mid=(high+low)/2;
		if(arr[mid]<val){
			low=mid+1;
		}
		else if(arr[mid]>val){
			high=mid-1;
		}
		else
			return mid;
	}
	return -1;
}