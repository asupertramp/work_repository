#include<stdio.h>
#include<string.h>
void replace_space(char *str)
{
	int originlen=strlen(str);
	int i,j,endlen,scnt=0;
	for(i=0;i<originlen;++i)
		if(*(str+i)==' ')
			scnt++;
	endlen=originlen+scnt*2;
	for(i=originlen-1,j=endlen-1;i>=0;--i,--j)
	{
		if(*(str+i)==' ')
		{
			*(str+j)='0';
			*(str+j-1)='2';
			*(str+j-2)='%';
			j-=2;
		}
		else
			*(str+j)=*(str+i);
	}
}
int main()
{
	char str[100]="i am a student ";
	printf("%s\n",str);
	replace_space(str);
	printf("%s\n",str);
	return 0;
}