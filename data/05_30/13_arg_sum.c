#include <stdio.h>
#include <stdarg.h>
#include <string.h>
#include <stdlib.h>

int add(int num, int a, int b, ...)
{
	int i;
	va_list ap;
	int sum  = a + b;

	/*printf("sum : %d\n", sum);*/
	va_start(ap, b);
	
	for (i = 0; i < num - 2; i++)
	{
		sum += va_arg(ap, int);
	}

	va_end(ap);

	/*printf("sum : %d\n", sum);*/
	return sum;
}

int add1(int a, int b, ...)
{
	int tmp;
	va_list ap;
	int sum = a + b;

	va_start(ap, b);

	while (1)
	{
		tmp = va_arg(ap, int);
		if (tmp == 0)
		{
			break;
		}
		sum += tmp;
	}
	va_end(ap);

	return sum;
}
int main(void)
{
	int ret;

	/*ret = add(2, 10, 20);*/
	ret = add1(10, 20, 30, 40, 0);
	printf("ret : %d\n", ret);
	ret = add1(3, 10, 20, 30, 0);
	printf("ret : %d\n", ret);
	ret = add1(5, 10, 0, 20, 30, 40, 50);
	printf("ret : %d\n", ret);




	return 0;
}
