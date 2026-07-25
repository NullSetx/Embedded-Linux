#include <stdio.h>
#include <stdarg.h>
#include <string.h>
#include <stdlib.h>

void init(int **p)
{
	printf("p : %p\n", p);
	*p = (int *)malloc(sizeof(int));
	/*p = (int **)malloc(sizeof(int *));*/

}
int main(void)
{
	int *p = NULL;

	//1 传参：no
	//2 返回：yes

	init(&p);

	*p = 123;

	return 0;
}
