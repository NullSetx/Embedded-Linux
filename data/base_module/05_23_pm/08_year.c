#include <stdio.h>
#include <stdarg.h>
#include <string.h>

int main(void)
{
	int year;

	printf("input year : ");
	scanf("%d", &year);

	if (year % 400 == 0)
	{
		printf("366!\n");
	}
	else
	{
		if (year % 4 == 0)
		{
			if (year % 100 != 0)
			{
				printf("366!\n");
			}
			else
			{
				printf("365!\n");
			}
		}
		else
		{
			printf("365!\n");
		}
	}
	printf("====================\n");
	if (year % 400 == 0 || year % 4 == 0 && year % 100 != 0)
	{
		printf("366!\n");
	}
	else
	{
		printf("365!\n");
	}
	return 0;
}
