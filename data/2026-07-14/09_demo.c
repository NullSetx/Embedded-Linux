#include <stdio.h>
#include <stdarg.h>
#include <string.h>
#include <stdlib.h>
#include <share.h>


int main(void)
{
	char buf[128];

	GETLINES("please input string : ", buf);
	printf("buf : %s\n", buf);
	return 0;
}
