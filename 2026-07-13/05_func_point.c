#include <stdio.h>
#include <stdarg.h>
#include <string.h>
#include <stdlib.h>

//函数名表示函数的地址
void test(void)
{
	printf("this is test!\n");
}

void hello(void)
{
	printf("this is hello!\n");
}
int add(int a, int b)
{
	printf("this is add!\n");
	return a + b;
}

int main(void)
{
	void *p = NULL;
	int ret;

	p = test;

	printf("test : %p\n", test);
	printf("p : %p\n", p);
	
	test();
	((void (*)(void))p)();

	printf("================\n");
	p = add;
	ret = ((int (*)(int, int))p)(2, 3);
	/*ret = add(2,3);*/
	printf("ret : %d\n", ret);
	/*p();*/
	/*p(2,3);*/

	/*p();*/
	return 0;
}
