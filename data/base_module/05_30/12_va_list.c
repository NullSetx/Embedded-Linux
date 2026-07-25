#include <stdio.h>
#include <stdarg.h>
#include <string.h>
#include <stdlib.h>

void test(int a, ...)
{
	va_list ap;

	//初始化
	va_start(ap, a);

	printf("first : %d\n", a);
	printf("second : %d\n", va_arg(ap, int));
	printf("third : %c\n", va_arg(ap, int));
	printf("four  : %f\n", va_arg(ap, double));
	printf("five  : %s\n", va_arg(ap, char *));
    /*
	 *printf("first : %d\n", a);
	 *printf("first : %f\n", *(&a + 1));
	 *printf("first : %c\n", *(&a + 2));
     */

	va_end(ap);	
}
int main(void)
{
    /*
	 *test(12);
	 *test(1, 2);
     */
	/*test(1234 , 222.33, 'A');*/

	test(123, 456, 'A', 33.44, "hello world");

	return 0;
}
