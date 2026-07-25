#include <stdio.h>
#include <stdarg.h>
#include <string.h>
#include <stdlib.h>

int main(void)
{
	int *p = NULL;

	p = (int *)malloc(sizeof(int));
	if (p == NULL)
	{
		printf("malloc false!\n");
		return -1;
	}
	printf("malloc success!\n");
	*p = 123;

	printf("*p : %d\n", *p);

	free(p);
	/*free(p);*/

	*p = 456;

	return 0;
}
