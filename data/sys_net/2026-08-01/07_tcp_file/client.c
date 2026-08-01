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

#define PORT 10086


//客户端
int main(int argc, char *argv[])
{
	int sd;
	int ret;
	struct sockaddr_in ser;
	char buf[128];
	int fd;

	if (argc != 4)
	{
		printf("format : cmd + ip + port + filename\n");
		return -1;
	}
	
	//1 创建网络套接子
	sd = socket(AF_INET, SOCK_STREAM, 0);
	ERRP(sd == -1, socket, goto ERR1);

	printf("sd : %d\n", sd);

	//2 请求建立链接
	ser.sin_family = AF_INET;
	ser.sin_port = htons(atoi(argv[2]));
	ser.sin_addr.s_addr = inet_addr(argv[1]);

	ret = connect(sd, (struct sockaddr *)&ser, sizeof(ser));
	ERRP(ret == -1, connect, goto ERR1);

	printf("conect success!\n");

	fd = open(argv[3], O_RDONLY);
	ERRP(fd == -1, open, goto ERR2);

	while (1)
	{
		memset(buf, 0, sizeof(buf));
		ret = read(fd, buf, sizeof(buf) - 1);
		if (ret == 0)
		{
			break;
		}

		send(sd, buf, ret, 0);
		sleep(1);
	}

	close(sd);
	close(fd);
	return 0;
ERR2:
	close(sd);
ERR1:
	return -1;
}
