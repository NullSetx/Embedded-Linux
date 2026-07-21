#include <stdio.h>
#include <stdarg.h>
#include <string.h>
#include <stdlib.h>

int main(void)
{
	printf("%s\n", "123");
	printf("%d\n", atoi("123"));
	printf("%d\n", atoi("hello"));
	printf("%d\n", atoi("123hello456"));
	return 0;
}
