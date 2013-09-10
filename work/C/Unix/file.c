#include<fcntl.h>
#include<stdio.h>
#define FILE_MODE (S_IRUSR|S_IWUSR|S_IRGRP|S_IROTH)
int main()
{
	int fd;
	if((fd=creat("a.txt",1))<0)
		fprintf(stderr,"creat error");
	exit(0);
}