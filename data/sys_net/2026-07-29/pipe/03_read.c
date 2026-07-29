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
	int fd[2];
	char buf[128] = {};

	ret = pipe(fd);
	ERRP(ret == -1, pipe, goto ERR1);

	printf("fd[0] : %d\n", fd[0]);
	printf("fd[1] : %d\n", fd[1]);

	ret = write(fd[1], "hello", 5);
	ERRP(ret != 5, write, goto ERR2);

	ret = read(fd[0], buf, sizeof(buf));
	ERRP(ret <= 0, read, goto ERR2);

	printf("buf : %s\n", buf);

	close(fd[0]);
	close(fd[1]);
	return 0;
ERR2:
	close(fd[0]);
	close(fd[1]);
ERR1:
	return -1;
}
