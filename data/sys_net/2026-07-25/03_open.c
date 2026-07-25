#include <stdio.h>
#include <stdarg.h>
#include <string.h>
#include <stdlib.h>
#include <share.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>

int main(int argc, char *argv[])
{
	int fd;

	//打开文件
	fd = open(argv[1], O_RDONLY);
	if (fd == -1)
	{
		perror("open");
		goto ERR1;
	}
	/*ERRP(fd == -1, open, goto ERR1);*/

	printf("fd : %d\n", fd);

	//关闭文件
	close(fd);
	return 0;
ERR1:
	return -1;
}
