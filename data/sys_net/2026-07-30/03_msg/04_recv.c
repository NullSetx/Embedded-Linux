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

int main(int argc, char *argv[])
{
	int msgid;
	key_t key;
	char buf[128];
	int ret;

	//1 获取创建消息对列key
	key = ftok(".", 123);
	ERRP(-1 == key, ftok, goto ERR1);

	PRI_H(key);
	//2 创建消息队列
	msgid = msgget(key, IPC_CREAT);
	ERRP(-1 == msgid, msgget, goto ERR1);

	printf("msgid : %d\n", msgid);

	//3 接受数据
	memset(buf, 0, sizeof(buf));
	ret = msgrcv(msgid, buf, sizeof(buf), 0, 0);
	ERRP(ret == -1, msgrcv, goto ERR1);

	PRI_S(buf);

	return 0;
ERR1:
	return -1;
}
