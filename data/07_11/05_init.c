#include <stdio.h>
#include <stdarg.h>
#include <string.h>
#include <stdlib.h>

//malloc calloc realloc => free
int main(void)
{
	int **p = NULL;

	//申请内存空间，先给高级指针申请，再给低级指针申请，且必须连续的
	p = (int **)malloc(sizeof(int *));
	if (p == NULL)
	{
		printf("malloc p false!\n");
		return -1;
	}
	*p = (int *)malloc(sizeof(int));
	if (*p == NULL)
	{
		printf("malloc *p false!\n");
		return -1;
	}

	**p = 123;

	//释放，则是由低到高，依次释放空间
	free(*p);
	*p = NULL;
	free(p);
	p = NULL;
	return 0;
}
