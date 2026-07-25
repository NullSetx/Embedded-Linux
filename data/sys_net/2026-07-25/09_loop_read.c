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
	int i;
	char buf[128];

	ERRP(-1 == (fd = open("./test", O_RDONLY)), open, goto ERR1);

	for (i = 0; i < 5; i++)
	{
		bzero(buf, sizeof(buf));
		read(fd, buf, sizeof(buf));
		printf("buf : %s\n", buf);
		lseek(fd, 0, SEEK_SET);
	}

	printf("size : %d\n", lseek(fd, 0, SEEK_END));
	return 0;
ERR1:
	return -1;
}
