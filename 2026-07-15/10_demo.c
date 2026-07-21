#include <stdio.h>
#include <stdarg.h>
#include <string.h>
#include <stdlib.h>
#include <share.h>

int main(int argc, char *argv[])
{
	FILE *fp = NULL;
	char ch = ' ';

	fp = fopen("./test", "w");
	ch = fgetc(fp);

	printf("ch : %c\n", ch);

	fputs("hello world", fp);

	fseek(fp, 0, SEEK_SET);

	ch = fgetc(fp);

	printf("ch : %c\n", ch);

	fclose(fp);
	return 0;
}
