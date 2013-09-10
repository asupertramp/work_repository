#include <stdio.h>

void merge(int *parr,int beginOffset,int middleOffset,int endOffset);
void mergeSort(int *parr,int beginOffset ,int endOffset);

int main(void)
{
    int i,arr[10]={1,43,11,7,9,40,2,34,6,8};
    mergeSort(arr,0,9);
    for(i=0;i<10;i++)
        printf("%d ",arr[i]);
    return 0;
}

void merge(int *parr, int beginOffset, int middleOffset, int endOffset)
{
    int leftLen,rightLen,len,i,j,k;
    int leftArr[10],rightArr[10];
    leftLen=middleOffset-beginOffset+1;
    rightLen=endOffset-middleOffset;
    len=leftLen+rightLen;
    if((beginOffset>middleOffset)||(middleOffset>=endOffset))
        return;
    for(i=0;i<leftLen;i++)
        leftArr[i]=parr[beginOffset+i];
    for(i=0;i<rightLen;i++)
        rightArr[i]=parr[middleOffset+1+i];
    j=0;
    k=0;
    for(i=beginOffset;i<=endOffset;i++)
    {
        if((j<leftLen)&&(k<rightLen))
        {
            if(leftArr[j]<rightArr[k])
            {
                parr[i]=leftArr[j];
                j++;
            }
            else
            {
                parr[i]=rightArr[k];
                k++;
            }
        }
        else if(j==leftLen)
        {
            parr[i]=rightArr[k];
            k++;
        }
        else if(k==rightLen)
        {
            parr[i]=leftArr[j];
            j++;
        }
    }
}

void mergeSort(int *parr, int beginOffset, int endOffset)
{
    int q=(endOffset+beginOffset)/2;
    if(beginOffset>=endOffset)
        return;
    mergeSort(parr,beginOffset,q);
    mergeSort(parr,q+1,endOffset);
    merge(parr,beginOffset,q,endOffset);
}
