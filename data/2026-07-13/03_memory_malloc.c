#include <stdio.h>
#include <stdarg.h>
#include <string.h>
#include <stdlib.h>

int main(void)
{
	int i;
	//指针数组 数组每一个成员都是指针
	char *name[10] = {};
	char buf[1024] = {};
/*
 *    printf("szieof(name) : %d\n", sizeof(name));//40
 *
 *    printf("sizeof(name[0]) : %d\n", sizeof(name[0]));//
 *    printf("strlen(name[0]) : %d\n", strlen(name[0]));//
 */

	for (i = 0; i < 3; i++)
	{
		printf("input name : ");
		fgets(buf, sizeof(buf), stdin);
		if (buf[strlen(buf) - 1] == '\n')
			buf[strlen(buf) - 1] = '\0';

		name[i] = (char *)malloc(strlen(buf) + 1);
		if (name[i] == NULL)
		{
			return -1;
		}
		strcpy(name[i], buf);
			
	}

	for (i = 0; i < 3; i++)
	{
		printf("%s\n", name[i]);
	}

	for (i = 0; i < 3; i++)
	{
		free(name[i]);
	}
	return 0;
}
