

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


#define INPUT 	10
#define OUTPUT 	5
#define PORT 10086

//zhangsan
//ztol => send
//ltoz => recv
int main(int argc, char *argv[])
{
	int fdr, fdw;
	char buf[128];
	int sd;
	int ret;
	struct sockaddr_in ser;

	//1 创建网络套接子
	sd = socket(AF_INET, SOCK_STREAM, 0);
	ERRP(sd == -1, socket, goto ERR1);

	//2 请求建立链接
	ser.sin_family = AF_INET;
	ser.sin_port = htons(PORT);
	ser.sin_addr.s_addr = inet_addr(argv[1]);

	ret = connect(sd, (struct sockaddr *)&ser, sizeof(ser));
	ERRP(ret == -1, connect, goto ERR2);



	system("clear");
	//创建进程
	if (fork() == 0)
	{
		//read
		printf("\033[%d;10Hlisi : ", OUTPUT);
		fflush(NULL);
		while (1)
		{
			read(sd, buf, sizeof(buf));
			printf("\033[%d;10Hlisi : \033[K%s\033[u", OUTPUT, buf);
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
		printf("\033[%d;10Hzhangsan : \033[K\033[s", INPUT);
		fgets(buf, sizeof(buf), stdin);
		if (buf[strlen(buf) - 1] == '\n')
			buf[strlen(buf) - 1] = '\0';
		
		write(sd, buf, strlen(buf) + 1);

		if (!strcmp(buf, "goodbye"))
		{
			break;
		}
	}

	wait(NULL);
	close(sd);
	return 0;
ERR2:
	close(sd);
ERR1:
	return -1;
}
