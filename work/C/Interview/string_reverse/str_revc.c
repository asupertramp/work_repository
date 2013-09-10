#include<stdio.h>
#include<string.h>
#include<stdlib.h>
char* rev1(char *str)
{
	char tmp;
	int i;
	int len=strlen(str);
	char* nstr=(char*)malloc(len+1);
	strcpy(nstr,str);
	for(i=0;i<len/2;i++)
	{
		tmp=*(nstr+i);
		*(nstr+i)=*(str+len-1-i);
		*(str+len-1-i)=tmp;
	}
	return nstr;
}
char* rev2(char *str)
{
	int i;
	int len=strlen(str);
	char *str_rev=(char*)malloc(len+1);
	strcpy(str_rev,str);
	char *p=str_rev;
	char *tmp=str_rev+len-1;
	for(i=0;i<len/2;++i)
	{
		*p^=*tmp;
		*tmp^=*p;
		*p^=*tmp;
		++p;
		--tmp;
	}
	return str_rev;
	
}
char* rev3(char *str)
{}
char* rev4(char *str)
{}
char* rev5(char *str)
{}
int revInplace(char *str,int length){
	if(length<=0)
		return 0;
	char *tail=str+length-1;
	char temp;
	while(str<tail){
		temp=*str;
		*str=*tail;
		*tail=temp;
		str++;
		tail--;
	}
	return 1;
}
int revSentence(char*str){
	int length=strlen(str);
	int wordlength=0;
	int newword=0;
	char *wordbegin;
	char temp;
	int i;
	if(length<=0)
		return 0;
	revInplace(str,length);
	for(i=0;i<length;i++){
		temp=*(str+i);
		if((temp==' ')&&(newword==1)){
			revInplace(wordbegin,wordlength);
			newword=0;
			wordlength=0;
			wordbegin=NULL;
		}
		else if(temp!=' '){
			if(newword==0){
				newword=1;
				wordbegin=str+i;
			}
			wordlength++;
		}
	}
	revInplace(wordbegin,wordlength);
	
	
}
int main(int argc,char* argv[])
{
	char *str="hello world";
	char arr[]="hello world";
	char sen[]="   hello world  C!";
	printf("length of str:%d\n",strlen(str));
	printf("sizeof of str:%d\n",sizeof(str));
	printf("length of arr:%d\n",strlen(arr));
	printf("sizeof of arr:%d\n",sizeof(arr));
	revInplace(arr,strlen(arr));
	printf("revInplace arr:%s\n",arr);
	revSentence(sen);
	printf("revSentence sen:%s\n",sen);
	char *str_rev=rev2(str);
	printf("%s,reversed:%s\n",str,str_rev);
	
	
	return 1;
}