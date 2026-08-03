

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


#define INPUT 10
#define OUTPUT 5
#define PORT 10086

//lisi
//ztol => recv
//ltoz => send
int main(int argc, char *argv[])
{
	char buf[128];
	int sd;
	struct sockaddr_in src, from;
	int fd;
	int len = sizeof(from);
	int ret;

	//1 创建网络套接子
	sd = socket(AF_INET, SOCK_STREAM, 0);
	ERRP(sd == -1, socket, goto ERR1);

	//2 绑定 
	src.sin_family = AF_INET;
	src.sin_port = htons(PORT);
	src.sin_addr.s_addr = inet_addr("192.168.2.254");
	ret = bind(sd, (struct sockaddr *)&src, sizeof(src));
	ERRP(ret == -1, bind, goto ERR2);

	printf("bind success!\n");

	//3 监听
	ret = listen(sd, 50);
	ERRP(ret == -1, listen, goto ERR2);
	
	printf("listen success!\n");

	//4 连接用户
	fd = accept(sd, (struct sockaddr *)&from, &len);
	ERRP(fd == -1, accept, goto ERR2);



	//创建进程
	system("clear");

	if (fork() == 0)
	{
		//read
		printf("\033[%d;10Hzhangsan : ", OUTPUT);
		fflush(NULL);
		while (1)
		{
			read(fd, buf, sizeof(buf));
			printf("\033[%d;10Hzhangsan : %s\033[K\033[u", OUTPUT, buf);
			fflush(NULL);
			if (!strcmp(buf, "goodbye"))
			{
				break;
			}
		}
		exit(0);
	}

	//parent write
	usleep(100);
	while (1)
	{
		printf("\033[%d;10Hlisi : \033[K\033[s", INPUT);
		fgets(buf, sizeof(buf), stdin);
		if (buf[strlen(buf) - 1] == '\n')
			buf[strlen(buf) - 1] = '\0';
		
		write(fd, buf, strlen(buf) + 1);

		if (!strcmp(buf, "goodbye"))
		{
			break;
		}
	}

	wait(NULL);
	close(fd);
	close(sd);
	return 0;

ERR3:
	close(fd);
ERR2:
	close(sd);
ERR1:
	return -1;
}
