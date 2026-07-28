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
#include <signal.h>

int main(int argc, char *argv[])
{
	if (fork() == 0)
	{
		printf("child!\n");
		sleep(1);
		kill(getppid(), 6);
	}
	else
	{
		while (1)
		{
			printf("parent!\n");
		}
	}
	return 0;
}
