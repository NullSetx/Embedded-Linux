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
	char ch = 'A';
	int ret;

	fd = open(argv[1], O_RDWR | O_CREAT | O_APPEND);
	ERRP(-1 == fd, open, goto ERR1);

	ERRP(write(fd, &ch, 1) != 1, write, goto ERR2);

	ch = ' ';

	ERRP(lseek(fd, 0, SEEK_SET) == -1, lseek, goto ERR2);


	ERRP((ret = read(fd, &ch, 1)) != 1, read, goto ERR2);
	/*ret = read(fd, &ch, 1);*/
	printf("ch : %c\n", ch);
	printf("ret : %d\n", ret);

	close(fd);
	return 0;
ERR2:
	close(fd);
ERR1:
	return -1;
}
