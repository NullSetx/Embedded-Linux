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

#define MAX 10

int main(int argc, char *argv[])
{
	int i;

	printf("main : pid = %d\n", getpid());

	for (i = 0; i < MAX; i++)
	{
		if (fork() == 0)
		{
			printf("child : pid = %d ppid = %d\n", getpid(), getppid());
			exit(0);
		}
	}
    /*
	 *if (fork() == 0)
	 *{
	 *    printf("child : pid = %d ppid = %d\n", getpid(), getppid());
	 *    exit(0);
	 *}
     */

	for (i = 0; i < MAX; i++)
	{
		wait(NULL);
	}	
	/*wait(NULL);*/
	return 0;
}
