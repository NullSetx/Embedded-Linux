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

int main(int argc, char *argv[])
{
	int sd;
	int ret ;
	struct sockaddr_in my_addr, from;
	char buf[1024] ={};
	int len = sizeof(from);
	
	if (argc != 2)
	{
		printf("format : cmd + port\n");
		return -1;
	}

	//1 创建套接子
	ERRP(-1 == (sd = socket(AF_INET, SOCK_DGRAM, 0)), socket, goto ERR1);

	//2 绑定
	my_addr.sin_family = AF_INET;//ctrl + p
	my_addr.sin_port = htons(atoi(argv[1]));
	my_addr.sin_addr.s_addr = htonl(INADDR_ANY);

	ret = bind(sd, (struct sockaddr *)&my_addr, sizeof(my_addr));
	ERRP(ret == -1, bind, goto ERR2);

	//3接受数据
	ret = recvfrom(sd, buf, sizeof(buf), 0, (struct sockaddr *)&from, &len);
	ERRP(ret == -1, recvfrom, goto ERR2);

	printf("ip : %s port : %d message : %s\n", inet_ntoa(from.sin_addr), ntohs(from.sin_port), buf);



	close(sd);
	return 0;
ERR2:
	close(sd);
ERR1:
	return -1;
}
