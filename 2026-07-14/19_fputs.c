#include <stdio.h>
#include <stdarg.h>
#include <string.h>
#include <stdlib.h>
#include <share.h>

int main(int argc, char *argv[])
{
	FILE *fp =  NULL;
	char buf[1024] = {};
	char *p = NULL;
	int ret;

	fp = fopen(argv[1], "w");
	ERRP(fp == NULL, fopen, goto ERR1);

	GETLINES("input write string : ", buf);
	
	ret = fputs(buf, fp);
	ERRP(ret == EOF, fputs, goto ERR2);


	fclose(fp);

	return 0;
ERR2:
	fclose(fp);
ERR1:
	return -1;
}
