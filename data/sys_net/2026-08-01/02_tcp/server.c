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


//服务器
int main(int argc, char *argv[])
{
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
	
	printf("accept success!\n");
	close(fd);
	close(sd);
	return 0;
ERR2:
	close(sd);
ERR1:
	return -1;
}
