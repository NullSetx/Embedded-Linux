#include <stdio.h>
#include <stdarg.h>
#include <string.h>
#include <stdlib.h>

void test(int num)
{
	if (num == 0)
		return ;

	printf("push : %d\n", num);
	test(num - 1);	
	printf("pop : %d\n", num);
}

int main(void)
{
	test(5);

	return 0;
}
