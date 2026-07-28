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

int main(int argc, char *argv[])
{
	int fd;

	int ret;
	struct rlimit rt;
	
	ret = getrlimit(RLIMIT_NOFILE, &rt);
	ERRP(ret == -1, getrlimit, goto ERR1);

	printf("rt.rlim_cur : %d\n", rt.rlim_cur);
	printf("rt.rlim_max : %d\n", rt.rlim_max);

	//设置文件描述符2000
	rt.rlim_cur = 3;
	ret = setrlimit(RLIMIT_NOFILE, &rt);
	ERRP(ret == -1, setrlimit, goto ERR1);

	while (1)
	{
		fd = open("./test", O_RDONLY);
		if (fd == -1)
		{
			break;
		}
		printf("fd : %d\n", fd);
	}
	return 0;
ERR1:
	return -1;
}
