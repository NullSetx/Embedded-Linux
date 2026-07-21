#include <stdio.h>
#include <stdarg.h>
#include <string.h>
#include <stdlib.h>

int main(void)
{
	printf("strstr(helloloe, lo) : %s\n", strstr("helloloe", "lo"));
	printf("strstr(helloloe, Lo) : %s\n", strstr("helloloe", "Lo"));
	printf("strcasestr(helloloe, Lo) : %s\n", strcasestr("helloloe", "Lo"));
	return 0;
}
