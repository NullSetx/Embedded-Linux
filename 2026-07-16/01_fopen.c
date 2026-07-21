#include <stdio.h>
#include <stdarg.h>
#include <string.h>
#include <stdlib.h>
#include <share.h>
#include <errno.h>//gf

int main(int argc, char *argv[])
{
	FILE *fp = NULL;

	fp = fopen(argv[1], "r");
	/*ERRP(fp == NULL, fopen, goto ERR1);*/
	if (fp == NULL)
	{
		perror("fopen");
		printf("errno : %d\n", errno);
		printf("styrerror : %s\n", strerror(13));
		printf("styrerror : %s\n", strerror(errno));
		goto ERR1;
	}

	fclose(fp);

	return 0;
ERR1:
	return -1;
}
