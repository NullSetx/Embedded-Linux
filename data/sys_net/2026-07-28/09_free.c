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
#include <sys/wait.h>

int **p = NULL;


void free_01(void)
{
	free(p);
}
void free_02(void)
{
	free(*p);
}

int main(int argc, char *argv[])
{
	
	p = (int **)malloc(sizeof(int *));

	*p = (int *)malloc(sizeof(int));

	atexit(free_01);//p
	atexit(free_02);//*p

    /*
	 *free(*p);
	 *free(p);
     */
	return 0;
}
