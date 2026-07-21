#include <stdio.h>
#include <stdarg.h>
#include <string.h>

int main(void)
{
	int a = 5, b = 2;

	printf("%d + %d = %d\n", a, b, a + b);//7
	printf("%d - %d = %d\n", a, b, a - b);//3
	printf("%d * %d = %d\n", a, b, a * b);//10
	printf("%d / %d = %d\n", a, b, a / b);//2
	printf("%d %% %d = %d\n", a, b, a % b);//

	/*a+++;*/
	++a;

	printf("a : %d\n", a);
	return 0;
}
