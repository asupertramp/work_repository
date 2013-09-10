#include<stdio.h>
#define IN 1
#define OUT 0
int main()
{
	int c;
	int state=OUT;
	int count=0;
	//printf("hello\c");error
	printf("\000 \001 \002 \003 \004 \005");
	printf("\006 \007 \010 \011 \012 \013");
	printf("\n\x61");
	printf("\nEOF is:%d",EOF);
	
	while((c=getchar())!=EOF)
	{
		putchar(c);
		if(c==' '||c=='\n')
		{
			state=OUT;
		}
		else 
		{
			if(state==OUT)
			{
				state=IN;
				++count;
			}
		}
		
	}
	printf("\nworld count:%d",count);
	return 1;
}