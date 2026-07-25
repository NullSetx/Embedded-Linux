#include <stdio.h>
#include <stdarg.h>
#include <string.h>

int main(void)
{
	int qq, passwd;

	printf("qq id : ");
	scanf("%d", &qq);

	if (qq == 8888888)
	{
		printf("input qq passwd : ");
		scanf("%d", &passwd);
		if (passwd == 123456)
		{
			printf("login success!\n");
		}
		else
		{
			printf("qq passwd input error!\n");
		}
	}
	else
	{
		printf("qq id input error!\n");
	}
	return 0;
}
