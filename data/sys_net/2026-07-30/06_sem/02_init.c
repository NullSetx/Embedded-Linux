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

int main(int argc, char *argv[])
{
	key_t key;
	int semid;
	int ret;
	int val = 1;

	key = ftok(".", 0x66);
	PRI_H(key);

	semid = semget(key, 1, IPC_CREAT);

	PRI_D(semid);

	//第一初始化锁，锁状态必须是打开状态
	//正数： 锁打开状态
	//负数： 锁关闭状态
	ret = semctl(semid, 0, SETVAL, val);
	ERRP(ret == -1, semctl, goto ERR1);


	return 0;
ERR1:
	return -1;
}






