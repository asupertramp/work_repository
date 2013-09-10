#include<stdio.h>
#include<string.h>
void remove_dump_charactor(char *str)
{
	int i,j,tail;
	int len=strlen(str);
	if(len<2)
		return;
	tail=1;
	for(i=1;i<len;++i)
	{
		for(j=0;j<i;++j)
			if(str[i]==str[j])
				break;
		if(i==j)
		{
			str[tail]=str[i];
			tail++;
		}
	}
	str[tail]='\0';
}
int main()
{
	char str1[]="hello world";
	char str2[]="abcdefghijk";
	char str3[]="aabbcccddddeeeee";
	char str4[]="abcabcabcabcd";
	remove_dump_charactor(str1);
	remove_dump_charactor(str2);
	remove_dump_charactor(str3);
	remove_dump_charactor(str4);
	printf("%s\n",str1);
	printf("%s\n",str2);
	printf("%s\n",str3);
	printf("%s\n",str4);
	return 0;
}
