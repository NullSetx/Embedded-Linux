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

#define LINE 1000

void do_work(int fd, const char *s)
{
	int i;
	char buf[128] = {};

	for (i = 0; i < LINE; i++)
	{
		snprintf(buf, sizeof(buf), "line : %d pid :%d data : %s\n",
			i, getpid(), s);
		write(fd, buf, strlen(buf));	
	}
	
}

int main(int argc, char *argv[])
{
	int fd;

	fd = creat(argv[1], 0644);
	ERRP(-1 == fd, creat, goto ERR1);

	if (fork() == 0)
	{
		sleep(1);
		do_work(fd, "child => hello");
		close(fd);
	}
	else
	{
		wait(NULL); //等待子进程先运行

		/*write(fd, "AAAAAAAAA\n", 10);*/
		do_work(fd, "parent => world");
		close(fd);
	}
	return 0;
ERR1:
	return -1;
}
