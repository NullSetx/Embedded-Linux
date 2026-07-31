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
#include "data.h"

int main(int argc, char *argv[])
{
	int msgid;
	key_t key;
	int ret;
	int fd;
	char ch;

	//1 获取创建消息对列key
	key = ftok(".", 123);
	ERRP(-1 == key, ftok, goto ERR1);

	PRI_H(key);
	//2 创建消息队列
	msgid = msgget(key, IPC_CREAT);
	ERRP(-1 == msgid, msgget, goto ERR1);

	printf("msgid : %d\n", msgid);

	fd = open(argv[1], O_RDONLY);
	ERRP(fd == -1, open , goto ERR1);

	while (1)
	{
		ret = read(fd, &ch, 1);
		if (ret == 0)
		{
			break;
		}
		//3 发送数据
		ret = msgsnd(msgid, &ch, 1, 0);
		if (ret == -1)
		{
			break;
		}
		/*usleep(100000);*/
	}
	return 0;
ERR1:
	return -1;
}
