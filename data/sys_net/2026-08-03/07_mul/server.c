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
	char ch;
	int val = 1;
	struct ip_mreqn mr;

	if (argc != 3)
	{
		printf("format : cmd + port + mul_ip\n");
		return -1;
	}

	//1 创建套接子
	ERRP(-1 == (sd = socket(AF_INET, SOCK_DGRAM, 0)), socket, goto ERR1);


	//设置端口重用
	ret = setsockopt(sd, SOL_SOCKET, SO_REUSEADDR, &val, sizeof(val));
	ERRP(ret == -1, setscokopt, goto ERR2);
	

	//2 绑定
	my_addr.sin_family = AF_INET;//ctrl + p
	my_addr.sin_port = htons(atoi(argv[1]));
	my_addr.sin_addr.s_addr = htonl(INADDR_ANY);
	ret = bind(sd, (struct sockaddr *)&my_addr, sizeof(my_addr));
	ERRP(ret == -1, bind, goto ERR2);

	//添加用户到多播组中
	mr.imr_multiaddr.s_addr = inet_addr(argv[2]);
	mr.imr_address.s_addr = htonl(INADDR_ANY);
	mr.imr_ifindex = 0;
	ret = setsockopt(sd, IPPROTO_IP, IP_ADD_MEMBERSHIP, &mr, sizeof(mr));
	ERRP(ret == -1, setsockopt add user, goto ERR2);


	//3接受数据
	while (1)
	{
		ret = recvfrom(sd, &ch, 1, 0, (struct sockaddr *)&from, &len);
		if (ret == -1)
		{
			break;
		}
		putchar(ch);
		fflush(NULL);//刷新缓冲区
	}
	/*printf("ip : %s port : %d message : %s\n", inet_ntoa(from.sin_addr), ntohs(from.sin_port), buf);*/

	//从多播破组中删除用户
	ret = setsockopt(sd, IPPROTO_IP, IP_DROP_MEMBERSHIP, &mr, sizeof(mr));
	ERRP(ret == -1, setsockopt del user, goto ERR2);


	close(sd);
	return 0;
ERR2:
	close(sd);
ERR1:
	return -1;
}
