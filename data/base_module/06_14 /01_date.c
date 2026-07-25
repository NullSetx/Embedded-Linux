#include <stdio.h>
#include <stdarg.h>
#include <string.h>
#include <stdlib.h>


int year(int days)
{
	int year = 1970;

	while (days > 365)
	{
		days -= 365 - is_year(year);
		year++;
	}

	return year;
}
int main(void)
{
	int days = (time(NULL) / 60 / 60 + 8) / 24;

	printf("time : %d:%d:%d\n", (time(NULL) / 60 / 60 + 8)% 24, time(NULL) / 60 % 60, time(NULL) % 60);

	printf("days : %d\n", days);

	printf("days : %d\n", count_year_days(1970, 2026) + count_month_days(6, 2026) + 14);
	//localtime(time(NULL))

	printf("year : %d\n", year(days));

	return 0;
}
