#include <stdio.h>
#include <stdarg.h>
#include <string.h>
#include <stdlib.h>
#include <share.h>

int main(int argc, char *argv[])
{
	FILE *fp = NULL;
	char ch;
	int ret;

	fp = fopen(argv[1], argv[2]);
	ERRP(fp == NULL, fopen, goto ERR1);

	while (1)
	{
		ch = fgetc(fp);
		if (ch == EOF)
		{
			break;
		}
		putchar(ch);

	}
	printf("================\n");
	/*rewind(fp);//指向文件开头*/
	fseek(fp, 0 ,SEEK_SET);
	while (1)
	{
		ch = fgetc(fp);
		if (ch == EOF)
		{
			break;
		}
		putchar(ch);

	}

    /*
	 *ret = fseek(fp, 1024 * 1024 * 1024, SEEK_SET);
	 *printf("ftell : %d\n", ftell(fp));
	 *
	 *fputc('A', fp);
     */

	#if 0
	ret = fseek(fp, 0, SEEK_END);
	printf("ftell : %d\n", ftell(fp));
	

	/*ret = fseek(fp, 4, SEEK_SET);*/
	ret = fseek(fp, -1, SEEK_END);
	ERRP(ret == -1, fseek, goto ERR2);
	

	ch = fgetc(fp);
	ERRP(ch == EOF, fgetc, goto ERR2);

	

	printf("ch : %c\n", ch);
	#endif

	fclose(fp);

	return 0;
ERR2:
	fclose(fp);
ERR1:
	return -1;
}
