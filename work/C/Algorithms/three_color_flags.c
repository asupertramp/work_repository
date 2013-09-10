#include<stdio.h>
#define BLUE 1
#define WHITE 2
#define RED 3

void swap(int *x,int *y)
{
	int temp;
	temp=*x;
	*x=*y;
	*y=temp;
}
void Three_color_flag(int color[], int n ) //����Ϊ��,��,�� 
{
    int white = 0 ; 
    int blue = 0 ; 
    int red = n - 1 ;
    while(white <= red)                      
    {
        if(color[white] == WHITE)  //��ɫ����Ϊ����,white++           
            white ++ ;                           
        else if(color[white] == BLUE ) //��ɫ����Ϊ��ɫ,�򽻻�,���߶�������,��+1       
              {
               swap(&color[blue],&color[white]);
               blue ++;                              
               white ++ ;
              }
        else                                       
        {
            while(white < red && color[red] == RED)//Ϊ��ɫ�����ɫ���򽻻�,��ɫ-1,��ɫ����,��Ϊ�������Ĳ�֪����ʲô��ɫ��  
                red --;                            
            swap(&color[red],&color[white]);
            red -- ;                          
        }
    }
	while(n--)
	{
		printf("%d,",color[n]);
	}
}

int main()
{
	int color[]={3,2,1,1,2,1,3,2,2,1};
	Three_color_flag(color,10);;
	
}