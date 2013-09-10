#include<stdio.h>
#include<string.h>
void weight(char *a,char *b,int len_a,int len_b)
{
	int i,j,tmp;
	int t[26];
	char ch[26];
	for(i=0;i<26;++i)
	{
		t[i]=0;
		ch[i]='a'+i;
	}
	for(i=0;i<len_a;++i)
		t[*(a+i)-'a']++;
	for(i=0;i<len_b;++i)
		t[*(b+i)-'a']--;
	for(i=0;i<25;++i)
		for(j=i+1;j<26;++j)
		{
			if(t[j]<t[i])
			{
				tmp=t[j];
				t[j]=t[i];
				t[i]=tmp;
				
				tmp=ch[j];
				ch[j]=ch[i];
				ch[i]=tmp;
			}
		}
	for(i=0;i<26;++i)
		printf("%c:%d\n",ch[i],i+1);
}

int main()
{
	char str1[255];
	char str2[255];
	scanf("%s",str1);
	scanf("%s",str2);
	weight(str1,str2,strlen(str1),strlen(str2));
	return 0;
}