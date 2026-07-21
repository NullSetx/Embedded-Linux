#include <stdio.h>
#include <stdarg.h>
#include <string.h>
#include <stdlib.h>

int main(void)
{
	printf("all_second : %d\n", time(NULL));
	printf("second : %d\n", time(NULL) % 60);
	return 0;
}
