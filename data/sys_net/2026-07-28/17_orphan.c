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

int main(int argc, char *argv[])
{
	
	if (fork() == 0)
	{
		while(1)
		{
			printf("child : pid = %d ppid = %d\n", getpid(), getppid());
			usleep(100000);
		}
		exit(0);
	}

	//parent
	printf("parent : pid = %d ppid = %d\n", getpid(), getppid());
	sleep(1);
	return 0;
}
