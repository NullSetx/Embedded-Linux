#include <stdio.h>
#include <stdarg.h>
#include <string.h>
#include <stdlib.h>

int main(void)
{
	char s1[128] = {};

	strcpy(s1, "world");
	printf("s1 : %s\n", s1);
	return 0;
}
