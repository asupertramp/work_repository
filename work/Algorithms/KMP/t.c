#include<stdio.h>
#include<stdlib.h>
void fun(int** p){
	int i;
	*p=(int*)malloc(10*sizeof(int));
}
void fun2(int a){
	printf("%d ",a);
}
int main(){
	int i,j,k;
	printf("%d\n",i+k+j);
	int **p;
	printf("%d ",&p);
	printf("%d ",p);
	fun2(i);
	//printf("%d ",*p);
	//printf("%d ",**p);
	
	//fun(p);
/*	for(i=0;i<10;i++)
		printf("%d,", **p);
	//free(p);*/
}