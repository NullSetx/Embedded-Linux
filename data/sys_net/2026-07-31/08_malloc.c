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

struct cls_t{
	int a;
	char name[64];
};


//线程执行流
////接受多级指针
//接受多少数据类型 => struct 
void *hello(void *data)
{
	printf("hello : %lu pid = %d\n", pthread_self(), getpid());

	printf("hello => data : %p\n", data);

	*(struct cls_t **)data = malloc(sizeof(struct cls_t));

	return NULL; //表示堆栈的返回
}

//
int main(int argc, char *argv[])
{
	
	int ret;
	pthread_t pthid = -1; //保存线程号
	int a = 1122;
	
	struct cls_t *cls = NULL; //线程申请空间，main就可以初始化


	printf("main : %lu pid = %d &cls = %p\n", 
		pthread_self(), getpid(), &cls);

	//对结构体普通变量, 不可以强制转换成指针类型
	ret = pthread_create(&pthid, NULL, hello, &cls);

	if (ret != 0)
	{
		return -1;
	}

	sleep(1);
	printf("==================\n");
	printf("pthid : %lu\n", pthid);

	cls->a = 123;
	strcpy(cls->name, "tom");

	//hello(&a);

	free(cls);

	return 0;//表示进程结束
}
