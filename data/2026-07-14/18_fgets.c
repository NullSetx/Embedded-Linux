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

	fp = fopen(argv[1], "r");
	ERRP(fp == NULL, fopen, goto ERR1);

	p = fgets(buf, sizeof(buf), fp);
	ERRP(p == NULL, fgets, goto ERR2);

	printf("%p : %s\n", buf, buf);
	printf("%p : %s\n", p, p);

	fclose(fp);

	return 0;
ERR2:
	fclose(fp);
ERR1:
	return -1;
}
