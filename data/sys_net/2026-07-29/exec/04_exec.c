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

int main(int argc, char *argv[], char **env)
{
	int ret;
	char *ar[] = {"ls", "-l", "-a", "-i", NULL};

	printf("main start ...pid : %d\n", getpid());
	/*system("ls");//fork()*/
	/*execl("./hello", "hello", NULL);*/
	/*ret = execl("/bin/ls", "ls", "-l", "-a", "-i", NULL);*/
	/*ret = execlp("ls", "ls", "-l", "-a", "-i", NULL);*/
	/*ret = execle("/bin/ls", "ls", "-l", "-a", "-i", NULL, env);*/
	/*ret = execv("/bin/ls", ar);*/
	ret = execve("/bin/ls", ar, env);
	ERRP(ret == -1, execl, goto ERR1);

	printf("main end ...\n");
	return 0;
ERR1:
	return -1;
}
