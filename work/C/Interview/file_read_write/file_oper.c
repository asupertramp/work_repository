#include<stdio.h>
#include<stdlib.h>

int readtoarray(int *a,FILE *fp)//���ļ��ｫ��������������
{
    int i=0;
	if(fp==NULL)
		exit(0);
	while(fgetc(fp)!=EOF)
    {
		fscanf(fp,"%d",&a[i]);
		printf("%d/n",a[i]);
		i++;
	}
	return i;
}
 
void writetofile(int a[],FILE *fp,int i)//������д���ļ���ȥ
{
    int k = 0;
 if(fp==NULL)
 {
  exit(0);
    }
    while(k<i)
    {
    fprintf(fp,"%c%d",' ',a[k++]); 
    }
}
 
void selectionSort(int *a,int i)//ѡ������
{
 int m,n;
    int tmp,min;
 for(m=0;m <i-1;m++)
 {
  min=m;
  for(n=m+1;n <i;n++)
  {
   if(a[n]<a[min]) 
    min=n;
  }
  tmp=a[m]; 
  a[m]=a[min]; 
  a[min]=tmp; 
 }
}

int main()
{
    FILE* fp,* fpwrite;
    int i;
    int a[10];
    fp=fopen("2.txt","r");
    i=readtoarray(a,fp);
    fclose(fp);
    selectionSort(a,i);
    fpwrite=fopen("2.txt","w");
    writetofile(a, fpwrite,i);
    fclose(fpwrite);
    return 0;
}