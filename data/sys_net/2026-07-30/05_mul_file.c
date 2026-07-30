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
#include <sys/ipc.h>
#include <sys/msg.h>
#include <sys/shm.h>

#define MAX 10
#define LINE 1000


void do_work(int fd)
{
	int i;
	char buf[128] = "hello world\n";
	/*printf("hello : pid = %d ppid = %d\n", getpid(), getppid());*/
	int line = LINE;
	while (line--)
	{
		/*snprintf(buf, sizeof(buf), "pid : %d line : %d\n", getpid(), line);*/
		for (i = 0; i < strlen(buf); i++)
		{
			write(fd, &buf[i], 1);
		}	
	}
}


int main(int argc, char *argv[])
{
	int fd;

	fd = creat(argv[1], 0666);
	ERRP(fd == -1, creat, goto ERR1);


	int i;
	for (i = 0; i < MAX; i++)
	{
		if (fork() == 0)
		{
			do_work(fd);
			exit(0);
		}
	}

	for (i = 0; i < MAX; i++)
	{
		wait(NULL);
	}



	return 0;
ERR1:
	return -1;
}
