#include <stdio.h>
#include <stdarg.h>
#include <string.h>
#include <stdlib.h>

int main(void)
{
	char ***p = NULL;

	
	p = (char ***)malloc(sizeof(char **));

	*p = (char **)malloc(sizeof(char *));

	**p = (char *)malloc(sizeof(char));


	***p = 'A';

	free(**p);
	free(*p);
	free(p);
	return 0;
}
