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
#include <sys/time.h>
#include <sys/resource.h>
#include <signal.h>

int main(int argc, char *argv[])
{
	int ret;

	if ((ret = fork()) == 0)
	{
		usleep(1000);
		printf("child!\n");
		kill(getppid(), 9);
		exit(0);
	}

	kill(ret, 2);
	printf("hello!\n");
	/*kill(getpid(), 1);*/
	/*kill(getpid(), SIGWINCH);*/
	kill(getpid(), SIGRTMIN+1);
	printf("world!\n");
	wait(NULL);
	return 0;
}
