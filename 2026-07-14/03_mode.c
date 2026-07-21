#include <stdio.h>
#include <stdarg.h>
#include <string.h>
#include <stdlib.h>

union op_t{
	char ch;
	int a;
};

int main(void)
{
	int i;
	int a = 0x11223344;
	union op_t op = {};

	op.ch = 1;
    /*
	 *0x01000000
	 *0x00000001 
     */
	if (op.a == 1)
	{
		printf("little!\n");
	}
	else
	{
		printf("big!\n");
	}
	for (i = 0; i < 4; i++)
	{
		printf("%p : %#x\n", ((char *)&a) + i, *(((char *)&a) + i));
	}

	if (*((char *)(&a)) == 0x44)
	{
		printf("little mode!\n");
	}
	else
	{
		printf("big mode!\n");
	}
	return 0;
}
