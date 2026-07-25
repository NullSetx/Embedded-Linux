#include <stdio.h>
#include <stdarg.h>
#include <string.h>
#include <stdlib.h>

void test(void)
{
	printf("this is test!\n");
}

int main(void)
{
	/*test(123, 3.44, "hello world", 'A');*/
	test(1);
	return 0;
}
