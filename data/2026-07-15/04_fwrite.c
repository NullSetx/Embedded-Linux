#include <stdio.h>
#include <stdarg.h>
#include <string.h>
#include <stdlib.h>
#include <share.h>

int main(int argc, char *argv[])
{
	FILE *fp = NULL;
	char buf[2000] = {};
	int ret;

	ERRP((fp = fopen(argv[1], "w")) == NULL, fopen, goto ERR1);

	GETLINES("input write string : ", buf);

	ret = fwrite(buf, sizeof(char), strlen(buf),fp);

	printf("ret : %d\n", ret);
	fclose(fp);

	return 0;
ERR1:
	return -1;
}
