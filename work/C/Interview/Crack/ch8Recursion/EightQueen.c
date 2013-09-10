#include<stdio.h>
#include <math.h>
int rowColumn[8];
int count;
int isConflict(int r,int c)
{
	int i;
	for(i=0;i<r;++i)
		if(rowColumn[i]==c||abs(rowColumn[i]-c)==abs(i-r))
			return 1;
	return 0;
}
void printBoard()
{
	int i,j;
	for(i=0;i<8;++i)
	{
		for(j=0;j<8;++j)
		{
			if(rowColumn[i]==j)
				printf("1");
			else
				printf("0");
		}
		printf("\n");
	}
	printf("\n");

}
void place(int row)
{
	int i;
	if(row==8)
	{
		printBoard();
		count++;
		return;
	}
	for(i=0;i<8;++i)
	{
		rowColumn[row]=i;
		if(!isConflict(row,i))
			place(row+1);
	}
}
int main()
{
	place(0);
	printf("%d\n",count);
	return 0;
}