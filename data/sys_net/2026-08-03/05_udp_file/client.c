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


//客户端
int main(int argc, char *argv[])
{
	int sd;
	int ret;
	struct sockaddr_in dest;
	int fd;
	char ch;


	if (argc != 4)
	{
		printf("format : cmd + port + ip + filename\n");
		return -1;
	}
	//1 创建建立连接套接子
	sd = socket(AF_INET, SOCK_DGRAM, 0);
	ERRP(sd == -1, socket, goto ERR1);

	//打开文件
	fd = open(argv[3], O_RDONLY);
	ERRP(fd == -1, open file, goto ERR2);


	//2 发送数据
	
	dest.sin_family = AF_INET;
	dest.sin_port = htons(atoi(argv[1]));
	dest.sin_addr.s_addr = inet_addr(argv[2]);

	while (1)
	{
		ret = read(fd, &ch, 1); 
		if (ret <= 0)
		{
			break;
		}

		ret = sendto(sd, &ch, 1, 0, (struct sockaddr *)&dest, sizeof(dest));
		usleep(100000);
	}

	/*printf("sento success!\n");*/

	close(fd);
	close(sd);
	return 0;
ERR2:
	close(sd);
ERR1:
	return -1;
}
