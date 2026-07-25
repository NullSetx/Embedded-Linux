#include <stdio.h>
#include <stdarg.h>
#include <string.h>
#include <stdlib.h>

int main(void)
{
	char name[128] = "";

	name[0] = 'Z';
	
	
	printf("name : %s\n", name);

	printf("input name : ");
	fgets(name, sizeof(name), stdin);
	if (name[strlen(name) - 1] == '\n')
		name[strlen(name) - 1]  = '\0';

	printf("strlen(name) : %d\n", strlen(name));
	/*gets(name);*/
	/*scanf("%s", name);*/
	printf("name : %s\n", name);
	return 0;
}
