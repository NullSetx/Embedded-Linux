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
	int status;

	if (fork() == 0)
	{
		abort();
		/*kill(getppid(), 6);*/
		/*kill(getppid(), SIGABRT);*/

		//8bit => 0 ~ 255
		exit(255 + 1);
		/*return int */
	}

	wait(&status);
	//判断子进程是正常退出还是异常退出
	//如果正常退出，则宏值为真，反之则为假
	printf("WIFEXITED(status) : %d\n", WIFEXITED(status));
	printf("status : %d\n", status);
	printf("WEXITSTATUS(status) : %d\n", WEXITSTATUS(status));

	printf("WIFSIGNALED(status) : %d\n", WIFSIGNALED(status));

	printf("WTERMSIG(status) : %d\n", WTERMSIG(status));
	return 0;
}
