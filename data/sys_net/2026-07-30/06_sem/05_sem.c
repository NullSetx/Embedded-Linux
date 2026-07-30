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

//表示加锁 负数
//0 表示加锁成功 -1表示解锁失败
int lock(int semid, int num)
{
	struct sembuf op;
	op.sem_num = num;
	op.sem_op = -1;
	op.sem_flg = 0;

	return semop(semid, &op, 1);
}

//解锁 正数 
int unlock(int semid, int num)
{
	struct sembuf op;
	op.sem_num = num;
	op.sem_op = 1;
	op.sem_flg = 0;

	return semop(semid, &op, 1);

}

int init_sem(void)
{
	key_t key;
	int ret;
	int val = 1;
	int semid;

	key = ftok(".", 0x66);
	PRI_H(key);

	semid = semget(key, 1, IPC_CREAT);

	PRI_D(semid);

	//第一初始化锁，锁状态必须是打开状态
	//正数： 锁打开状态
	//负数： 锁关闭状态
	ret = semctl(semid, 0, SETVAL, val);
	ERRP(ret == -1, semctl, goto ERR1);


	return semid;
ERR1:
	return -1;
}






