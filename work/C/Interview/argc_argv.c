#include<stdio.h>
int main(int argc ,char* argv[])
{
	int c=0;
	while(c<argc)
		printf("%s ",argv[c++]);
	while(--argc>0&&(*++argv)[0]=='-')
		while(c=(*++argv[0]))
		{
			switch(c)
			{
				case 'a':
					printf("a\n");
					break;
				case 'b':
					printf("b\n");
					break;
				default:
					putchar(c);
					break;
			}
			
		}
	return 0;
}