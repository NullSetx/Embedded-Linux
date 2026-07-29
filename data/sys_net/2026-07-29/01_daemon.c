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
	int count = 0;
/*
 *    daemon(0, 0);
 *
 *    while (1)
 *    ;
 */
	#if 1
	int fd;
	int ret;
	int fd1;

	ret = daemon(0, 0);
	ERRP(ret == -1, daemon, goto ERR1);

	fd1 = open("/dev/stdout", O_RDWR);
	write(fd1, "hello\n", 6);

#if 1
	fd = creat("/tmp/test", 0644);
	ERRP(fd == -1, creat, goto ERR1);
#endif
	while (1)
	{
		if (count == 100)
		{
			break;
		}
		write(fd, "hello\n", 6);
		count++;	
		usleep(1000000);
	}
	close(fd);
	#endif
	return 0;
ERR1:
	return -1;
}
