#include <stdio.h>
#include <stdarg.h>
#include <string.h>
#include <stdlib.h>
#include <share.h>

int main(int argc, char *argv[])
{
	FILE *fp = NULL;

	char name[64] = "";
	int age = 0;

	fp = fopen(argv[1], "r");

	fscanf(fp, "%s : %d", name, &age);

	printf("name : %s age : %d\n", name, age);
	fclose(fp);
	return 0;
}
