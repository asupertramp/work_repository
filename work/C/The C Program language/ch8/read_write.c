#include<stdio.h>
#include<stdarg.h>
#include<stdlib.h>
void error(char *fmt,...);
#define BUFSIZE 1024
int main()
{
	int buf[BUFSIZE];
	int n=0;
	//error("test error(),%d,%d",n,n+1);
	//creat("test.txt",0777);
	while((n=read(0,buf,BUFSIZE))>0)
		write(1,buf,n);
	return 0;
}
int mygetchar(void)
{
	char c;
	return read(0,&c,1)==1?(unsigned char)c:EOF;
}
int myputchar(int c)
{
	char tmp=c;
	
}
void error(char *fmt,...)
{
	va_list var;
	
	va_start(var,fmt);
	fprintf(stderr,"error:");
	vfprintf(stderr,fmt,var);
	fprintf(stderr,"\n");
	va_end(var);
	exit(1);
}