#include <stdio.h>
#include <stdarg.h>
#include <string.h>
#include <stdlib.h>
#include <share.h>

int main(int argc, char *argv[])
{
	FILE *fp = NULL;

	char name[64] = "zhangsan";
	int age = 18;

	fp = fopen(argv[1], "w");

	fprintf(fp, "%s : %d", name, age);

	fclose(fp);
	return 0;
}
