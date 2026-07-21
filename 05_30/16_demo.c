#include <stdio.h>
#include <stdarg.h>
#include <string.h>
#include <stdlib.h>

//实现
void hello(void)
{
	hello();//调用自己
	printf("hello!\n");


}
int main(void)
{
	/*hello();*/

	while (1)
	{
		printf("hello!\n");
	}
	return 0;
}
