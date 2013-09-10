#include <stdio.h>

int findMin(int *parr,int beginOffset, int endOffset);
void selectionSort(int *parr, int arrLen);
int main(void)
{
    int i;
    int test[6]={5,2,4,52,12,42};
    selectionSort(test,6);
    for(i=0;i<6;i++)
    {
        printf("%d ",test[i]);
    }

}

int findMin(int *parr,int beginOffset, int endOffset)
{
    int minOffset=beginOffset;
    int i;
    for(i=beginOffset;i<=endOffset;i++)
    {
        if(*(parr+i)<*(parr+minOffset))
            minOffset=i;
    }
    return minOffset;
}

void selectionSort(int *parr,int arrLen)
{
    int i,j,temp;
    for(i=0;i<arrLen;i++)
    {
        j=findMin(parr,i,arrLen-1);
        temp=parr[j];
        parr[j]=parr[i];
        parr[i]=temp;
    }
}
