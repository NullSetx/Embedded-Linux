#include <stdio.h>
#include <stdarg.h>
#include <string.h>
#include <stdlib.h>

int main(void)
{
	unsigned char ch;// -128 ~ 127
	// 0 ~ 255
	ch = 127 + 1;

	ch = 255 + 1;
	printf("ch : %d\n", ch);

	register int a;
	return 0;
}
