#include <stdio.h>
#include <stdarg.h>
#include <string.h>
#include <stdlib.h>
#include <share.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>

//取消键盘阻塞
void cancel_block(int fd)
{
	int flag ;

	//键盘默认是可读可写
	flag = fcntl(fd, F_GETFL);
	printf("flag : %#o\n", flag);

	flag |= O_NONBLOCK;
	fcntl(fd, F_SETFL, flag);

}


int main(int argc, char *argv[])
{
	char name[64] = "tom";
	
	cancel_block(0);

	while (1)
	{
		printf("%s\n", name);
		scanf("%s", name);
	}
	return 0;
}
