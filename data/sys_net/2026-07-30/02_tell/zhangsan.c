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

#define INPUT 	10
#define OUTPUT 	5

//zhangsan
//ztol => send
//ltoz => recv
int main(int argc, char *argv[])
{
	int fdr, fdw;
	char buf[128];

	if (access("./ztol", F_OK) == -1)
	{
		if (mkfifo("./ztol", 0666) == -1)
		{
			goto ERR1;
		}
	}

	if (access("./ltoz", F_OK) == -1)
	{
		if (mkfifo("./ltoz", 0666) == -1)
		{
			goto ERR2;
		}
	}

	fdw = open("./ztol", O_RDWR);
	ERRP(-1 == fdw, zhangsan write, goto ERR3);

	fdr = open("./ltoz", O_RDWR);
	ERRP(-1 == fdr, zhangsan read, goto ERR4);

	system("clear");
	//创建进程
	if (fork() == 0)
	{
		//read
		printf("\033[%d;10Hlisi : ", OUTPUT);
		fflush(NULL);
		while (1)
		{
			read(fdr, buf, sizeof(buf));
			printf("\033[%d;10Hlisi : \033[K%s\033[u", OUTPUT, buf);
			fflush(NULL);
			if (!strcmp(buf, "goodbye"))
			{
				break;
			}
		}
		exit(0);
	}

	//parent write
	usleep(100);
	while (1)
	{
		printf("\033[%d;10Hzhangsan : \033[K\033[s", INPUT);
		fgets(buf, sizeof(buf), stdin);
		if (buf[strlen(buf) - 1] == '\n')
			buf[strlen(buf) - 1] = '\0';
		
		write(fdw, buf, strlen(buf) + 1);

		if (!strcmp(buf, "goodbye"))
		{
			break;
		}
	}

	wait(NULL);
	close(fdr);
	close(fdw);
	unlink("./ltoz");
	unlink("./ztol");
	return 0;
ERR4:
	close(fdw);
ERR3:
	unlink("./ltoz");
ERR2:
	unlink("./ztol");
ERR1:
	return -1;
}
