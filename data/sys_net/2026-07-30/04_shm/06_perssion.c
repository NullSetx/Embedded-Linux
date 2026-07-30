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

int main(int argc, char *argv[])
{
	key_t key;
	int shmid;


	//1 关键字
	key = ftok(".", 0x55);
	ERRP(-1 == key, ftok, goto ERR1);

	PRI_H(key);

	//2 创建
	shmid = shmget(key, 1024, IPC_CREAT | 0666);
	ERRP(-1 == shmid, shmget, goto ERR1);

	PRI_D(shmid);
	

	return 0;
ERR1:
	return -1;
}
