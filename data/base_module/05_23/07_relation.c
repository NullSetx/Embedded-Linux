#include <stdio.h>
#include <stdarg.h>
#include <string.h>

int main(void)
{
	int a = 5, b = 3;

	printf("a > b : %d\n", a > b);	//1
	printf("a >= b : %d\n", a >= b);//1
	printf("a < b : %d\n", a < b);//0
	printf("a <= b : %d\n", a <= b);//0
	printf("a == b : %d\n", a == b);//0
	printf("a != b : %d\n", a != b);//1
	return 0;
}
