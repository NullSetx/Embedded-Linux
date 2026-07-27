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


int e = 12345;//DS
//heap => malloc calloc realloc

int main(int argc, char *argv[])
{
	int ret;

	ret = fork();
	if (ret == -1)
	{
		printf("fork false!\n");
		return -1;
	}
	else if (ret == 0)
	{
		
		printf("child!pid = %d ppid = %d\n", getpid(), getppid());
		printf("child e = %d\n", e);
		e = 5678;
		printf("child e = %d\n", e);
	}
	else
	{
		sleep(1);
		printf("parent!pid = %d ppid = %d\n", getpid(), getppid());
		printf("parnet e = %d\n", e);
	}
	return 0;
}
