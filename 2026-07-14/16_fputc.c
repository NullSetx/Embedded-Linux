#include <stdio.h>
#include <stdarg.h>
#include <string.h>
#include <stdlib.h>
#include <share.h>

int main(int argc, char **argv)
{
	FILE *fp = NULL;
	int ch = 'A';
	int ret;

	fp = fopen(argv[1], "w");
	ERRP(fp == NULL, fopen, goto ERR1);

	printf("fopen success!\n");
	
	ret = fputc(ch, fp);
	ERRP(ret == EOF, fputc, goto ERR2);

	printf("ret : %c\n", ret);


	fclose(fp);
	return 0;
ERR2:
	fclose(fp);
ERR1:
	return -1;
}
