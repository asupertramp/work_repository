#include<stdio.h>

void package(int n,float c,float v[],float w[],float x[]);
void package0_1(int n,float c,float v[],float w[],float x[]); 

int main(void)
{
    int n = 3;
    float c = 20;
    float v[] = {24,15,25};
    float w[] = {15,10,18};//�Ѿ����յ�λ��ֵ��������
    float *x;
    x = (float*)malloc(sizeof(float)*n); 
    printf("******����*******\n");
    package(n,c,v,w,x);
    printf("*******0-1����******\n");
    package0_1(n,c,v,w,x);
    system("PAUSE");

}

/*
*  �������� 
*  n:��Ʒ���� 
*  c���������� 
*  v[]:ÿ����Ʒ�ļ�ֵ 
*  w[]:ÿ����Ʒ�������������Ѿ����յ�λ��ֵ�������� �� 
*  x[]:��Ʒ�Ƿ���뱳����0��ʾ���ţ�1��ʾȫ�����룬0-1����һ���֣� 
*/
void package(int n,float c,float v[],float w[],float x[])
{
     int i;
     for(i=0;i<n;i++)
     {
        x[i] = 0;//��ʼ״̬��������Ʒ��û�б����뱳�� 
     } 
     
     for(i=0;i<n;i++)
     {
       if(w[i] > c)
       {
         break;
       }
       
       x[i] = 1;
       c = c - w[i];
       printf("�����%d����Ʒ������ʣ������%f.\n",(i+1),c);
     }
     
     if(i<=n)//�����Է���һ����Ʒ��һ���� 
     {
        x[i] = c/w[i]; 
        
        printf("�����%d����Ʒ��%f����.����ʣ������Ϊ0.\n",(i+1),w[i]*x[i]);
     }     
}

/*
*  0-1�������� 
*  n:��Ʒ���� 
*  c���������� 
*  v[]:ÿ����Ʒ�ļ�ֵ 
*  w[]:ÿ����Ʒ�������������Ѿ����յ�λ��ֵ�������� �� 
*  x[]:��Ʒ�Ƿ���뱳����0��ʾ���ţ�1��ʾȫ�����룩 
*/
void package0_1(int n,float c,float v[],float w[],float x[])
{
     int i;
     for(i=0;i<n;i++)
     {
        x[i] = 0;//��ʼ״̬��������Ʒ��û�б����뱳�� 
     } 
     
     for(i=0;i<n;i++)
     {
       if(w[i] > c)
       {
         break;
       }
       
       x[i] = 1;
       c = c - w[i];
       printf("�����%d����Ʒ������ʣ������%f.\n",(i+1),c);
     }
}

 
