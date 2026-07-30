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
	struct cls_t cls;
	struct tea_t tea;

	//1 获取创建消息对列key
	key = ftok(".", 123);
	ERRP(-1 == key, ftok, goto ERR1);

	PRI_H(key);
	//2 创建消息队列
	msgid = msgget(key, IPC_CREAT);
	ERRP(-1 == msgid, msgget, goto ERR1);

	printf("msgid : %d\n", msgid);

	//3 接受数据
	if (atoi(argv[1]) == 1)
	{
		ret = msgrcv(msgid, &cls, sizeof(struct cls_t), atoi(argv[1]), 0);
		ERRP(ret == -1, msgrcv, goto ERR1);

		printf("name : %s sex : %c id : %d\n",
			cls.name, cls.sex, cls.id);
	}
	else
	{
		//老师
		ret = msgrcv(msgid, &tea, sizeof(struct tea_t), atoi(argv[1]), 0);
		ERRP(ret == -1, msgrcv, goto ERR1);

		printf("name : %s age : %d\n",
			tea.name, tea.age);
	}
	return 0;
ERR1:
	return -1;
}
