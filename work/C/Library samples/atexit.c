#include<stdlib.h>
#include<stdio.h>

void exit_f1(void)
{
	printf("Exit function 1\n");
}
void exit_f2(void)
{
	printf("Exit function 2\n");
}

int main()
{
	atexit(exit_f1);
	atexit(exit_f2);
	return 0;
}