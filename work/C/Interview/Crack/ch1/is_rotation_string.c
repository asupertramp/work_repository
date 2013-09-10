/*只调用一次issubstring(),判断字符串a是否是b的旋转字符串。解：构造字符串b+b*/
#include<stdio.h>
#include<string.h>
int is_substring(char *s,char* sub)
{
	int i;
	int l=strlen(s);
	int sl=strlen(sub);
	if(l<sl)
		return 0;
	for(i=0;i<l-sl+1;++i)
		if(strncmp(s+i,sub,sl)==0)
			return 1;
	return 0;
}

int is_rotation_string(char *a,char *b)
{
	char temp[1024];
	strcat(temp,b);
	strcat(temp,b);
	return is_substring(temp,a);
}
int main()
{
	char *str1="abcdefg";
	char *str2="cdefgab";
	char *str3="cdefgabde";
	if(is_rotation_string(str1,str2))
				printf("%s is rotation string of %s\n",str1,str2);
}