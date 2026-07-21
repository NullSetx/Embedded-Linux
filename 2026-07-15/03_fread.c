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

	ERRP((fp = fopen(argv[1], "r")) == NULL, fopen, goto ERR1);

	ret = fread(buf, 1, sizeof(buf) - 1,fp);

	printf("ret : %d\n", ret);
	printf("buf : %s\n", buf);
	return 0;
ERR1:
	return -1;
}
