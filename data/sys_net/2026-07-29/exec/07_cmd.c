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
	int fd[2];

	pipe(fd);

	if (fork() == 0)
	{
		close(fd[0]);
		//child cat /etc/passwd
		dup2(fd[1], 1);
		execlp("cat", "cat", "/etc/passwd", NULL);//1
		/*fd[1]*/
		exit(0);
	}

	close(fd[1]);
	wait(NULL);
	//parent grep root
	dup2(fd[0], 0);
	execlp("grep", "grep", "root", NULL);
	return 0;
}
