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
	char buf[1024];

	ERRP(NULL == (fpr = fopen(argv[1], "r")), fopen read, goto ERR1);
	ERRP(NULL == (fpw = fopen(argv[2], "w")), fopen write, goto ERR2);

	while (1)
	{
		memset(buf, 0, sizeof(buf));
		ret = fread(buf, 1, sizeof(buf) - 1, fpr);
		if (ret == 0)
		{
			break;
		}
		printf("ret : %d\n", ret);
		/*fwrite(buf, 1, strlen(buf), fpw);*/
		fwrite(buf, 1, ret, fpw);
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
