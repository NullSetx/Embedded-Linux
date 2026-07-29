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
	int fd;
	char buf[128] = {};

	ret = access(argv[1], F_OK);
	if (ret != 0)
	{
		ret = mkfifo(argv[1], 0644);
		ERRP(ret == -1, mkfifo, goto ERR1);

		printf("mkfifo success!\n");
	}

	fd = open(argv[1], O_RDWR);
	ERRP(fd == -1, open, goto ERR2);
	
	while (1)
	{
		read(fd, buf, sizeof(buf));
		printf("message : %s\n", buf);
		if (strcmp(buf, "exit") == 0)
		{
			break;
		}
	}

	close(fd);
	unlink(argv[1]);
	return 0;
ERR2:
	unlink(argv[1]);
ERR1:
	return -1;
}
