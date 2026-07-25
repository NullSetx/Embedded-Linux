#include "stack.h"


void ls(const void *data)
{
	putchar(*((char *)data));
}

int main(int argc, char *argv[])
{
	int i;
	char buf[128];
	STACK *handle = NULL;
	char ch = '\n';

	handle = stack_creat(sizeof(char), 1024);
	ERRP(NULL == handle, stack_creat, goto ERR1);


	GETLINES("input string : ", buf);

	printf("buf : %s\n", buf);

	for (i = 0; i < strlen(buf); i++)
	{
		if (buf[i] == '#')
		{
			stack_pop(handle);
		}
		else if (buf[i] == '@')
		{
			stack_push(handle, &ch);		
		}
		else
		{
			stack_push(handle, &buf[i]);
		}
	}

	stack_travel(handle ,ls);
	putchar(10);
	return 0;

ERR1:
	return -1;
}
