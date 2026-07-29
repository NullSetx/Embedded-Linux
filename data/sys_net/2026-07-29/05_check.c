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

typedef void (*sighandler_t)(int);

int main(int argc, char *argv[])
{
	int i;
	sighandler_t ret;

	for (i = 1; i <= 64; i++)
	{
		ret = signal(i, SIG_DFL);
		if (ret == SIG_ERR)
		{
			printf("%d ", i);
		}
	}
	return 0;
}
