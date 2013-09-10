#include<stdio.h>
#include<stdarg.h>
void myPrintf(char *fmt,...)
{
	va_list ap;
	int ival;
	char *sval;
	float fval;
	char *p;
	
	va_start(ap,fmt);
	for(p=fmt;*p;++p)
	{
		if(*p!='%')
		{
			putchar(*p);
			continue;
		}
		switch(*++p)
		{
			case 'd':
				ival=va_arg(ap,int);
				printf("%d",ival);
				break;
			case 'f':
				fval=va_arg(ap,double);
				printf("%f",fval);
				break;
			case 's':
				for(sval=va_arg(ap,char*);*sval;++sval)
					putchar(*sval);
				break;
		}
	}
	va_end(ap);
}

int main()
{
	char *str="defg";
	myPrintf("2+3=%d  ",2+3);
	myPrintf("abc%s",str);
	return 0;
}