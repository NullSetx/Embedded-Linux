#include <stdio.h>
#include <stdarg.h>
#include <string.h>
#include <stdlib.h>
#include <share.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>

int main(int argc, char *argv[])
{
	int fd;

	umask(0);

	fd = open(argv[1], O_CREAT, S_IRWXU | S_IRWXG | S_IRWXO);
	ERRP(-1 == fd, open, goto ERR1);

	close(fd);
	return 0;
ERR1:
	return -1;
}
