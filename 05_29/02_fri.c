#include <stdio.h>
#include <stdarg.h>
#include <string.h>

int main(void)
{
	int i;
	int year = 2026;
	int days = 0;

	printf("input year : ");
	scanf("%d", &year);

	for (i = 1900; i < year; i++)
	{
		days += 365;
		if (i % 400 == 0 || i % 4 == 0 && i % 100 != 0)
		{
			days += 1;
		}
	}
	printf("days : %d\n", days);

	days += 13;

	for (i = 1; i <= 12; i++)
	{
		if (days % 7 == 5)
		{
			printf("%d年%d月13日是黑色星期五!\n", year, i);
		}
		if (i == 1 || i == 3 || i == 5 || i == 7 ||
			i == 8 || i == 10 || i == 12)
		{
			days += 31;
		}
		else if (i == 2)
		{
			days += 28;
			if (year % 400 == 0 || year % 4 == 0 && year % 100 != 0)
			{
				days += 1;
			}
		}
		else 
		{
			days += 30;
		}
	}

	return 0;
}
