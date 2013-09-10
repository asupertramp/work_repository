#include<stdio.h>
char binary[100];
void printbinary(float a)
{
	int intPart=(int) a;
	float decPart=a-intPart;
	printf("%d,%f",intPart,decPart);
}
int main()
{
	float a;
	scanf("%f",&a);
	printbinary(a);
	return 0;
}