#include <stdio.h>
#include <stdarg.h>
#include <string.h>
#include <stdlib.h>
#include <share.h>
#include "stack.h"

void ls(const void *data)
{
	printf("%d", *((int *)data));
}

int main(int argc, char *argv[])
{
	int i;
	int num;
	char buf[1024];
	STACK *handle = NULL;
	int *val1 = NULL, *val2 = NULL;

	handle = stack_creat(sizeof(int), 100);

	GETLINES("input string : ", buf);

	for (i = strlen(buf); i >= 0; i--)
	{
		if (buf[i] >= '0' && buf[i] <= '9')
		{
			num = buf[i] - 48;
			stack_push(handle, &num);
		}
	}

	stack_travel(handle, ls);
	putchar(10);

	for (i = 0; i < strlen(buf); i++)
	{
		if (buf[i] == '+' || buf[i] == '-' || buf[i] == '*' ||
			buf[i] == '/' || buf[i] == '%')
		{
			val1 = (int *)stack_pop(handle);
			/*printf("val1 : %d\n", *val1);*/
			if (val1 == NULL)
			{
				break;
			}
			val2 = (int *)stack_pop(handle);
			/*printf("val2 : %d\n", *val2);*/
			if (val2 == NULL)
			{
				printf("result : %d\n", *val1);
				return 0;
			}
			switch (buf[i])
			{
				case '+':
					*val1 += *val2;
					break;
				case '-':
					*val1 -= *val2;
					break;
				case '*':
					*val1 *= *val2;
					break;
				case '/':
					*val1 /= *val2;
					break;
				case '%':
					*val1 %= *val2;
					break;
			}
			stack_push(handle, val1);
		}
	}
	printf("result : %d\n", *(int *)stack_pop(handle));

	stack_destroy(&handle);

	return 0;
}
