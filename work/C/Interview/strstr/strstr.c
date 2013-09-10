#include<stdio.h>
#include<string.h>

int my_strstr(const char *str,const char *substr)
{
	if(str==NULL||substr==NULL)
		return -1;
	size_t len=strlen(str);
	size_t sublen=strlen(substr);
	if(len<sublen)
		return -1;
	int i,j;
	for(i=0;i<len-sublen;++i)
	{
		for(j=0;j<sublen;++j)
		{
			if(str[i+j]!=substr[j])
				break;
		}
		if(j==sublen)
			return i+1;
	}
	return -1;
}

char *my_strcpy(char *dst,const char *src)
{
	if(dst==NULL||src==NULL)
		return NULL;
	if(dst==src)
		return dst;
	char *addr=dst;
	while((*dst++=*src++)!='\0')
		;
	return addr;
}

int main()
{
	char str[]="abcdefg";
	char sub[]="cde";
	printf("%d",my_strstr(str,sub));
	return 0;
}