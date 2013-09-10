#include <stdio.h>
#include <string.h>
#include <time.h>
int main(void)
{
	struct tm t;
	char str[80];
	/* sample loading of tm structure */
	t.tm_sec = 1; /* Seconds */
	t.tm_min = 30; /* Minutes */
	t.tm_hour = 9; /* Hour */
	t.tm_mday = 22; /* Day of the Month */
	t.tm_mon = 11; /* Month */
	t.tm_year = 56; /* Year - does not include century */
	t.tm_wday = 4; /* Day of the week */
	t.tm_yday = 0; /* Does not show in asctime */
	t.tm_isdst = 0; /* Is Daylight SavTime; does not show in asctime */
	/* converts structure to null terminated
	string */
	strcpy(str, asctime(&t));
	printf("%s\n", str);
	return 0;
}