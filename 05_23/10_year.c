#include <stdio.h>
#include <stdarg.h>
#include <string.h>

int main(void)
{
	int year;

	printf("input year : ");
	scanf("%d", &year);

	printf("year : %d\n", year);


	((year % 4 == 0 && year % 100 != 0) || year % 400 == 0) ? printf("366!\n") : printf("365!\n");

	return 0;
}
