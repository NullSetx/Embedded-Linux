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


//线程执行流
void *hello(void *data)
{
	printf("hello : %lu pid = %d\n", pthread_self(), getpid());

	printf("data : %d\n", *(int *)data);

	*(int *)data = 3344;


	return NULL; //表示堆栈的返回
}

int main(int argc, char *argv[])
{
	
	int ret;
	pthread_t pthid = -1; //保存线程号
	int a = 1122;


	printf("main : %lu pid = %d\n", pthread_self(), getpid());

	ret = pthread_create(&pthid, NULL, hello, &a);
	if (ret != 0)
	{
		return -1;
	}

	sleep(1);
	printf("==================\n");
	printf("pthid : %lu\n", pthid);
	printf("main : a = %d\n", a);

	//hello(&a);


	return 0;//表示进程结束
}
