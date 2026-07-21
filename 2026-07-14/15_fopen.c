#include <stdio.h>
#include <stdarg.h>
#include <string.h>
#include <stdlib.h>
#include <share.h>

int main(int argc, char **argv)
{
	FILE *fp = NULL;
	int ch;

	fp = fopen(argv[1], "r");
	ERRP(fp == NULL, fopen, goto ERR1);

	printf("fopen success!\n");

	printf("EOF : %d\n", EOF);
	//-1 => 补码 => 0000 0000 0000 0000 0000 0000 0001
	//			 => 1111 1111 1111 1111 1111 1111 1110 + 1
	//			 => 1111                          1111
	while (1)
	{
		ch = fgetc(fp);
		if (ch == EOF)
		{
			break;
		}
		/*ERRP(ch == EOF, fgetc, goto ERR2);*/
		
		printf("ch : %c\n", ch);
		getchar();
	}

	fclose(fp);
	return 0;
ERR2:
	fclose(fp);
ERR1:
	return -1;
}
