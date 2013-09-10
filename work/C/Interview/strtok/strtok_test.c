#include<stdio.h>
#include<string.h>
void print_tokens(char *line)
{
	static char whitespace[]=" \t\f\r\v\n";
	char *token;
	for(token=strtok(line,whitespace);token!=NULL;token=strtok(NULL,whitespace))
		printf("%s\n",token);
}
int main()
{
	char line[]="i am a boy\n you   are \n a \n girl";
	print_tokens(line);
	return 0;
}