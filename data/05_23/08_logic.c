#include <stdio.h>
#include <stdarg.h>
#include <string.h>

int main(void)
{
	int a = 5, b = 3, c = 0;
	// (a || b) && c => 0
	// a || (b && c) => 1
	printf("a || b && c: %d\n", (a || b) && c);
	/*printf("a && b && c < b: %d\n", a && b && (c < b));*/

	printf("!!a : %d\n", !!a);
	//A 5 B -5 C 1 D 0
	

	b = 3;
	/*a || ++b;*/
	a = 0;
	a && ++b;

	printf("b : %d\n", b);

	return 0;
}
