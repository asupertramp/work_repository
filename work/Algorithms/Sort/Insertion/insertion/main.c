#include <stdio.h>

int main(void)
{
    int arr[8]={25,54,12,57,888,465,25,157};
    int i,j,temp;
    for(i=1;i<8;i++)
    {
        temp=arr[i];
        for(j=i-1;(j>=0)&&(arr[j]>temp);j--)
                arr[j+1]=arr[j];
        arr[j+1]=temp;
    }
    for(i=0;i<8;i++)
        printf("%d ",arr[i]);
    return 1;

}

