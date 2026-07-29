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

	ret = access(argv[1], F_OK);
	if (ret != 0)
	{
		ret = mkfifo(argv[1], 0644);
		ERRP(ret == -1, mkfifo, goto ERR1);

		printf("mkfifo success!\n");
	}

	printf("data option!\n");
	return 0;
ERR1:
	return -1;
}
