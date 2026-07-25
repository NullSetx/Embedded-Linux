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
	int fd1, fd2;

	fd1 = open("./test", O_WRONLY | O_CREAT | O_TRUNC);
	ERRP(fd1 == -1, open zhangsan, goto ERR1);
	printf("fd1 : %d\n", fd1);

	write(fd1, "hello", 5);

	/*fd2 = open("./test", O_WRONLY | O_CREAT | O_TRUNC);*/
	/*fd2 = dup(fd1);*/
	fd2 = dup2(fd1, 1);
	ERRP(fd1 == -1, open lisi, goto ERR1);
	printf("fd2 : %d\n", fd2);
	write(fd2, "world", 5);

	
	return 0;
ERR1:
	return -1;
}
