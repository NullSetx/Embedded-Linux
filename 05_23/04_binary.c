#include <stdio.h>
#include <stdarg.h>
#include <string.h>

int main(void)
{
	int a = 10;

	a = 20;

	printf("a : %d\n", a);
	printf("&a : %p\n", &a);
    /*
	 *printf("a : %d\n", a);
	 *printf("a : %o\n", a);
	 *printf("a : %#o\n", a);
	 *printf("a : %x\n", a);
	 *printf("a : %X\n", a);
	 *printf("a : %#x\n", a);
	 *printf("a : %#X\n", a);
     */
	return 0;
}
