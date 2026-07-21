#include <stdio.h>
#include <stdarg.h>
#include <string.h>

int main(void)
{
	int result;

	printf("input result : ");
	scanf("%d", &result);

	if (result >= 60)
	{
		printf("恭喜你上岸成功 ^_^\n");
		printf("hello!\n");
	}	
	return 0;
}
