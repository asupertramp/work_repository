#include<stdio.h>

void package(int n,float c,float v[],float w[],float x[]);
void package0_1(int n,float c,float v[],float w[],float x[]); 

int main(void)
{
    int n = 3;
    float c = 20;
    float v[] = {24,15,25};
    float w[] = {15,10,18};//已经按照单位价值降序排列
    float *x;
    x = (float*)malloc(sizeof(float)*n); 
    printf("******背包*******\n");
    package(n,c,v,w,x);
    printf("*******0-1背包******\n");
    package0_1(n,c,v,w,x);
    system("PAUSE");

}

/*
*  背包问题 
*  n:物品个数 
*  c：背包容量 
*  v[]:每个物品的价值 
*  w[]:每个物品的重量（这里已经按照单位价值降序排列 ） 
*  x[]:物品是否放入背包（0表示不放，1表示全部放入，0-1放入一部分） 
*/
void package(int n,float c,float v[],float w[],float x[])
{
     int i;
     for(i=0;i<n;i++)
     {
        x[i] = 0;//初始状态，所有物品都没有被放入背包 
     } 
     
     for(i=0;i<n;i++)
     {
       if(w[i] > c)
       {
         break;
       }
       
       x[i] = 1;
       c = c - w[i];
       printf("放入第%d件物品，背包剩余容量%f.\n",(i+1),c);
     }
     
     if(i<=n)//还可以放入一个物品的一部分 
     {
        x[i] = c/w[i]; 
        
        printf("放入第%d件物品的%f部分.背包剩余容量为0.\n",(i+1),w[i]*x[i]);
     }     
}

/*
*  0-1背包问题 
*  n:物品个数 
*  c：背包容量 
*  v[]:每个物品的价值 
*  w[]:每个物品的重量（这里已经按照单位价值降序排列 ） 
*  x[]:物品是否放入背包（0表示不放，1表示全部放入） 
*/
void package0_1(int n,float c,float v[],float w[],float x[])
{
     int i;
     for(i=0;i<n;i++)
     {
        x[i] = 0;//初始状态，所有物品都没有被放入背包 
     } 
     
     for(i=0;i<n;i++)
     {
       if(w[i] > c)
       {
         break;
       }
       
       x[i] = 1;
       c = c - w[i];
       printf("放入第%d件物品，背包剩余容量%f.\n",(i+1),c);
     }
}

 
