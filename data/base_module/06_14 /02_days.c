#include <stdio.h>
#include <stdarg.h>
#include <string.h>

//统计年的总天数
//统计月的总天数
//判断是否是润年
//函数声明
int count_year_days(int sy, int ey);
int count_month_days(int month, int year);
int is_year(int year);

//函数实现
int count_year_days(int sy, int ey)
{
	int i, days = 0;

	for (i = sy; i < ey; i++)
	{
		days += 365 + is_year(i);
	}

	return days;
}
int is_year(int year)
{
	if (year % 400 == 0 || year % 4 == 0 && year % 100 != 0)
		return 1;
	return 0;	
}

int count_month_days(int month, int year)
{
	int i, days = 0;

	for (i = 1; i < month; i++)
	{
		if (i == 1 || i == 3 || i == 5 || i == 7 ||
			i == 8 || i == 10 || i == 12)
		{
			days += 31;
		}
		else if (i == 2)
		{
			days += 28 + is_year(year);
		}
		else 
		{
			days += 30;
		}
	}

	return days;
}

