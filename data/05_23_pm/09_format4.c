#include <stdio.h>
#include <stdarg.h>
#include <string.h>

int main(void)
{
	int sel;

	printf("input sel : ");
	scanf("%d", &sel);
	if (sel == 1)
	{
		printf("led1 on!\n");
	}
	else if (sel == 2)
	{
		printf("led2 on!\n");
	}
	else if (sel == 3)
	{
		printf("buzzer on!\n");
	}
	else if (sel == 4)
	{
		printf("buzzer off!\n");
	}
	else
	{
		printf("input err!\n");
	}
	return 0;
}
