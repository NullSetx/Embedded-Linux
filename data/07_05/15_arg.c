#include <stdio.h>
#include <stdarg.h>
#include <string.h>
#include <stdlib.h>

void test_01(int *p)
{

}

void test_02(char *p)
{

}

void test_all(const void *p)
{
	printf("&p : %p p : %p\n", &p, p);
	*(char *)p = 12;
}
int main(void)
{
	
	int a = 10;
	char ch = 'A';

    /*
	 *test_01(&a);
	 *test_02(&ch);
     */
	test_all(&a);
	printf("a : %d\n", a);
	test_all(&ch);
	printf("a : %d\n", a);
	return 0;
}
