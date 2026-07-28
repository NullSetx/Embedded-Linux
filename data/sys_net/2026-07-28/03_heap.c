#include <stdio.h>
#include <stdarg.h>
#include <string.h>
#include <stdlib.h>
#include <share.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>
#include <pwd.h>
#include <grp.h>
#include <shadow.h>
#include <time.h>
#include <dirent.h>

int main(int argc, char *argv[])
{
	int * p = NULL;

	p = (int *)malloc(100);
	ERRP(NULL == p, malloc, goto ERR1);


	if (fork() == 0)
	{
		printf("child!\n");
		*p = 123;
		printf("child : *p = %d\n", *p);
		free(p);
		p = NULL;
	}
	else
	{
		sleep(1);
		printf("parent!\n");
		*p = 456;
		free(p);
	}

	return 0;
ERR1:
	return -1;
}
