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


void do_work(int fd, struct sockaddr_in from)
{
	char buf[128];

	while (1)
	{
		//5 接受数据
		read(fd, buf, sizeof(buf));
		printf("ip : %s port : %d message : %s\n",
			inet_ntoa(from.sin_addr), ntohs(from.sin_port), buf);

		if (!strcmp(buf, "exit"))
		{
			break;
		}
	}	

}


//服务器
int main(int argc, char *argv[])
{
	int sd;
	struct sockaddr_in src, from;
	int fd;
	int len = sizeof(from);
	int ret;
	char buf[102400];
	int fd1;

	if (argc != 3)
	{
		printf("format : cmd + port + filename\n");
		return -1;
	}
	//1 创建网络套接子
	sd = socket(AF_INET, SOCK_STREAM, 0);
	ERRP(sd == -1, socket, goto ERR1);

	//2 绑定 
	src.sin_family = AF_INET;
	src.sin_port = htons(atoi(argv[1]));
	/*src.sin_addr.s_addr = inet_addr("192.168.2.254");*/
	src.sin_addr.s_addr = INADDR_ANY;//表示本地ip
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

	fd1 = creat(argv[2], 0666);
	ERRP(fd == -1, creat, goto ERR3);

	while (1)
	{
		//5 接受数据
		memset(buf, 0, sizeof(buf));
		ret = recv(fd, buf, sizeof(buf), 0);
		if (ret == 0)
		{
			break;
		}
		write(fd1, buf, ret);

		/*printf("%s", buf);*/
	}
	/*close(fd1);*/

	
	

	close(fd1);
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
