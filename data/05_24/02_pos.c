#include <stdio.h>
#include <stdarg.h>
#include <string.h>

int main(void)
{
	int x, y;

	printf("input x and y : ");
	scanf("%d%d", &x, &y);

	if (x > 0 && y > 0)
	{
		printf("第一象限!\n");
	}
	else if (x < 0 && y > 0)
	{
		printf("第二象限!\n");
	}

	return 0;
}
