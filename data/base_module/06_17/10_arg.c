#include <stdio.h>
#include <stdarg.h>
#include <string.h>
#include <stdlib.h>

void show(char name[][10])
{
	printf("name[0] : %s\n", name[0]);
	strcpy(name[0],"hello");
	printf("name[0] : %s\n", name[0]);
}

int main(void)
{
	char name[10][10] = {"tom", "jim", "mary"};

	show(name);
	printf("main => name[0] : %s\n", name[0]);

	return 0;
}
