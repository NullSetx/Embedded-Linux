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

	//1 创建网络套接子
	sd = socket(AF_INET, SOCK_STREAM, 0);
	ERRP(sd == -1, socket, goto ERR1);

	printf("sd : %d\n", sd);

	//2 请求建立链接
	ser.sin_family = AF_INET;
	ser.sin_port = htons(PORT);
	ser.sin_addr.s_addr = inet_addr(argv[1]);

	ret = connect(sd, (struct sockaddr *)&ser, sizeof(ser));
	ERRP(ret == -1, connect, goto ERR1);

	printf("conect success!\n");



	close(sd);

	return 0;
ERR1:
	return -1;
}
