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

int main(int argc, char *argv[])
{
	int ret;
	int count = 1122;//stack

	ret = fork();
	if (ret == -1)
	{
		printf("fork false!\n");
		return -1;
	}
	else if (ret == 0)
	{
		sleep(1);
		printf("child!pid = %d ppid = %d\n", getpid(), getppid());
		printf("child : count = %d &count = %p\n", count, &count);
		count = 3344;
		printf("child : count = %d\n", count);
		printf("child : a = %d\n", *(&count - 1));

	}
	else
	{
		//运行时段的堆栈
		int a = 9999;//stack
		printf("parent!pid = %d ppid = %d\n", getpid(), getppid());
		printf("parent : count = %d &count = %p\n", count, &count);
		printf("parent : a = %d &a = %p\n",a, &a);
	}
	return 0;
}
