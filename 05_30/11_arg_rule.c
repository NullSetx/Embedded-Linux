#include <stdio.h>
#include <stdarg.h>
#include <string.h>
#include <stdlib.h>

void test(int a, float f, char ch)
{
	printf("this is test!\n");
	printf("a : %d\n", a);
}

int main(void)
{
	/*test(123, 3.44, 'A');*/
	//参数个数要保持一致
	/*test(123, 3.44, 'A', "hello");*/
	/*test(123, 3.44);*/

	//参数类型要保持一致
	/*test(3.45, "hello", 567);*/


	//参数顺序要保持一致
	test(3.44, 'A', 1122);



	return 0;
}
