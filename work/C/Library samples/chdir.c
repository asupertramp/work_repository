#include<dir.h>
#include<stdio.h>
#include<stdlib.h>
#define MAXDIR 100
char old_dir[MAXDIR];
char new_dir[MAXDIR];

int main()
{
	if(getcurdir(0,old_dir))
	{
		perror("getcurdir()");
		return  1;
	}
	printf("current  directory:%s\n",old_dir);
	if(chdir("\\"))
	{
		perror("chdir()");
		return 1;
	}
	if(getcurdir(0,new_dir))
	{
		perror("getcurdir()");
		return  1;
	}
	printf("current  directory:%s\n",new_dir);
	return 0;
	
}