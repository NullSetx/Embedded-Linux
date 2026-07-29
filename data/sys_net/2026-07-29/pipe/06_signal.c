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

void hello(int sig)
{
	printf("sig : %d\n", sig);
}
int main(int argc, char *argv[])
{
	char buf[128];
	int ret;
	int fd[2];


	ERRP(signal(SIGPIPE, hello) == SIG_ERR, signal, goto ERR1);

	ret = pipe(fd);
	ERRP(ret == -1, pipe, goto ERR1);

	if (fork() == 0)
	{
		//child
        /*
		 *close(fd[0]);
		 *close(fd[1]);
         */
        /*
		 *while (1)
		 *{
		 *    close(fd[1]);
		 *    read(fd[0], buf, sizeof(buf));
		 *    if (strcmp(buf, "exit") == 0)
		 *    {
		 *        break;
		 *    }
		 *    printf("message : %s\n", buf);
		 *}	
         */

		exit(0);
	}

	close(fd[0]);
	sleep(1);
	while (1)
	{
		write(fd[1], "hello", 6);
        /*
		 *GETLINES("input string : ", buf);
		 *write(fd[1], buf, strlen(buf) + 1);
		 *if (strcmp(buf, "exit") == 0)
		 *{
		 *    break;
		 *}
         */
	}
	
	wait(NULL);

	close(fd[0]);
	close(fd[1]);

	return 0;
ERR1:
	return -1;
}
