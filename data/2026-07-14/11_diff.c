#include <stdio.h>
#include <stdarg.h>
#include <string.h>
#include <stdlib.h>
#include <share.h>

#define TEST(a, b) a##b

#define PRI(a) printf(#a" : %d\n", a)

int main(void)
{
	int a = 10;
	int b = 20;
	int result = 99;
	
	int TEST(a, b) = 123;

	printf("ab : %d\n", ab);


	PRI(a);
	PRI(b);
	PRI(result);
	return 0;
}
