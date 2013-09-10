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
void Three_color_flag(int color[], int n ) //排序为蓝,白,红 
{
    int white = 0 ; 
    int blue = 0 ; 
    int red = n - 1 ;
    while(white <= red)                      
    {
        if(color[white] == WHITE)  //白色区域为白旗,white++           
            white ++ ;                           
        else if(color[white] == BLUE ) //白色区域为蓝色,则交换,两边都处理了,各+1       
              {
               swap(&color[blue],&color[white]);
               blue ++;                              
               white ++ ;
              }
        else                                       
        {
            while(white < red && color[red] == RED)//为红色则与红色区域交换,红色-1,白色不变,因为换过来的不知道是什么颜色的  
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