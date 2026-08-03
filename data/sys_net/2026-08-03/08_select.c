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
#include <sys/ipc.h>
#include <sys/msg.h>
#include <sys/shm.h>
#include <sys/sem.h>
#include <pthread.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <netinet/ip.h>
#include <arpa/inet.h>
#include <sys/select.h>


int main(int argc, char *argv[])
{
	int fd;
	fd_set fdr;
	char buf[128] = {};
	int ret;
	struct timeval it = {0, 0};
	//键盘 => 0
	//管道 => 
	fd = open("./ken", O_RDWR);
	ERRP(fd == -1, open, goto ERR1);

	while (1)
	{
		FD_ZERO(&fdr);
		FD_SET(0, &fdr);//键盘
		FD_SET(fd, &fdr);//管道文件
		/*ret = select(fd + 1, &fdr, NULL, NULL, NULL);*/
		ret = select(fd + 1, &fdr, NULL, NULL, NULL);
		if (ret == -1)
		{
			return -1;
		}
		else if (ret == 0)
		{
			printf("time out!\n");
		}
		else
		{
			//用户输入
			if (FD_ISSET(fd, &fdr))
			{
				//管道文件
				memset(buf, 0, sizeof(buf));
				read(fd, buf, sizeof(buf));
				printf("fifo : %s\n", buf);


			}
			else if (FD_ISSET(0, &fdr))
			{
				//input
				memset(buf, 0, sizeof(buf));
				read(0, buf, sizeof(buf));
				printf("stdin : %s\n", buf);
				write(fd, buf, strlen(buf) + 1);
			}

		}

	}
	
	return 0;
ERR1:
	return -1;
}
