#include<stdio.h>
#include<stdlib.h>
int main(){
	int arr[]={1,2,3,4,5,6,7,8,7,6,5,4,3,2,1};
	int length=sizeof(arr)/sizeof(int);
	printf("%d\n",length);
	int i,xor=0;
	for(i=0;i<length;i++)
		xor^=arr[i];
	printf("%d",xor);
}