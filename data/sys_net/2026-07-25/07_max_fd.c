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

	// 0 ~ 1023 => 1024
	while (1)
	{
		fd = open(argv[1], O_RDONLY);
		if (fd == -1)
		{
			break;
		}
		printf("fd : %d\n", fd);
	}

	return 0;
}
