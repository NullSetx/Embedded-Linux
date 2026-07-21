#include <stdio.h>
#include <stdarg.h>
#include <string.h>
#include <stdlib.h>
#include <share.h>

int main(int argc, char *argv[])
{
	FILE *fp = NULL;

	fp = fopen(argv[1], "w");
	ERRP(NULL == fp, fopen, goto ERR1);

	fputc('A', fp);
	fclose(fp);

	getchar();

	fclose(fp);
	return 0;
ERR1:
	return -1;
}
