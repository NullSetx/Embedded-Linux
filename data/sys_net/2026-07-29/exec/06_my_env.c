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
	char *my_ar[] = {"hello", "world", "123", "test", NULL};
	char *my_env[] = {"name=tom", "id=100086", "sex=F", NULL};

	execve("/ken/sys_net/2026-07-29/exec/access", my_ar, my_env);

	return 0;
}
