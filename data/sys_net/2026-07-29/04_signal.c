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

void hello(int sig)
{
	printf("hello!\n");
}

int main(int argc, char *argv[])
{
	sighandler_t ret;

	ret = signal(2, hello);//自定义
	/*ret = signal(2, SIG_IGN);//忽略*/
	ERRP(ret == SIG_ERR, signal, goto ERR1);

    /*
	 *sleep(5);
	 *ret = signal(2, SIG_DFL);//默认
     */

	getchar();

	return 0;
ERR1:
	return 0;
}
