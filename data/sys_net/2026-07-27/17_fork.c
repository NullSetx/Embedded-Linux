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
	}
	else
	{
		printf("parent!pid = %d ppid = %d\n", getpid(), getppid());
		printf("parent!ret = %d\n", ret);
	}
	return 0;
}
