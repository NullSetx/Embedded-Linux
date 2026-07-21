#include <stdio.h>
#include <stdarg.h>
#include <string.h>
#include <stdlib.h>
#include <share.h>

int main(int argc, char *argv[])
{
	FILE *fpr = NULL, *fpw = NULL;
	int ch;
	int ret;

	ERRP(NULL == (fpr = fopen(argv[1], "r")), fopen read, goto ERR1);
	ERRP(NULL == (fpw = fopen(argv[2], "w")), fopen write, goto ERR2);

	while (1)
	{
		ch = fgetc(fpr);
		if (ch == EOF)
		{
			break;
		}
		ret = fputc(ch, fpw);
		ERRP(ret == EOF, fputc, goto ERR3);

	}

	fclose(fpw);
	fclose(fpr);

	return 0;
ERR3:
	fclose(fpw);
ERR2:
	fclose(fpr);
ERR1:
	return -1;
}
