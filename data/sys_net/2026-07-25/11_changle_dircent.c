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
	int fd1;

	fd = open("./test", O_WRONLY | O_CREAT | O_APPEND);

	/*fd1 = fcntl(fd, F_DUPFD, 0);//fd1 = dup(fd)*/
	/*fd1 = fcntl(fd, F_DUPFD, 88);// fd1 = dup2(fd, 88);*/
	close(1);
	fd1 = fcntl(fd, F_DUPFD, 1);// fd1 = dup2(fd, 88);


	write(1, "test", 4);

    /*
	 *dup2(fd, 1);
	 *dup2(fd, 2);
     */
	/*write(1, "hello", 5);*/
	/*printf("hello\n");//1*/
	/*fprintf(stderr, "AAAAAA");*/

	return 0;
}
