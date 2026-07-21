#include <stdio.h>
#include <stdarg.h>
#include <string.h>
#include <stdlib.h>

int main(void)
{
	char name[64] = {};
	char *s = NULL;

	
	//fgets => name => strlen => malloc => strcpy
	fgets(name, sizeof(name), stdin);
	if (name[strlen(name) - 1] == '\n')
		name[strlen(name) - 1] = '\0';

	printf("name : %s\n", name);	

	s = (char *)malloc(strlen(name) + 1);// +1 表示尾零也需要一个空间
	if (s == NULL)
	{
		return -1;
	}

	strcpy(s, name);

	printf("s : %s\n", s);

	free(s);
	return 0;
}
