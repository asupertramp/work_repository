//统计输入中单词长度的分布直方图
#include<stdio.h>
#define MAXHIST	20
#define MAXCNT	15
#define MAXLEN	15
#define IN		1
#define OUT		0
int main()
{
	int c,i,j,nc,state,maxval;
	int wc[MAXLEN];
	nc=0;
	for(i=0;i<MAXLEN;++i)
		wc[i]=0;
	printf("plese input a sentence\n");
	while((c=getchar())!=EOF)
	{
		if(c==' '||c=='\n'||c=='\t')
		{
			if(nc>0)
				++wc[nc-1];
			nc=0;
			state=OUT;
		}
		else if(state==OUT)
		{
			nc=1;
			state=IN;
		}
		else
		{
			++nc;
		}
	}
	maxval=0;
	for(i=0;i<MAXLEN;++i)
		if(wc[i]>maxval)
			maxval=wc[i];
	
	for(j=MAXHIST;j>0;--j)
	{
		for(i=0;i<MAXLEN;++i)
		{
			if(wc[i]*MAXLEN/maxval>j)
				printf("*\t");
			else
				printf(" \t");
		}
		printf("\n");
	}
	for(i=1;i<=MAXLEN;++i)
		printf("%d\t",i);
	return 1;
} 