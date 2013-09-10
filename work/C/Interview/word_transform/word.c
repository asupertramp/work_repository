#include<stdio.h>
#define TRUE 1
#define FALSE 0
int isSimilar(char *a,char *b)
{
	int i ,j=0;
	if(strlen(a)!=strlen(b))
		return FALSE;
	for(i=0;i<strlen(a);++i)
	{
		if(j>1)
			return FALSE;
		if(*(a+i)!=*(b+i))
			j++;
	}
	if(j==0)
		return FALSE;
	else
		return TRUE;
}
int main()
{
	char *words[]={"dog","dot","cog","dug","hug","but","hello","helo"};
	int i,j;
	for(i=0;i<sizeof(words)/sizeof(char*)-1;++i)
		for(j=i;j<sizeof(words)/sizeof(char*);++j)
			if(isSimilar(words[i],words[j]))
				printf("%s,%s\n",words[i],words[j]);
	return 1;
}