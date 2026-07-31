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

int e = 3344;

//线程执行流
void *hello(void *data)
{
	static int a = 1122; //不要返回非静态局部变量的地址 
	//如果返回，则访问数据的时候可能被替换掉

	printf("hello : %lu pid = %d &a = %p\n", 
		pthread_self(), getpid(), &a);

	sleep(1);
	//返回malloc申请的空间地址 => 调用结束后，则需要free
	pthread_exit(data);
	pthread_exit(&a);//静态变量的地址
	pthread_exit(&e);//全局变量可以返回

	/*return NULL; //表示堆栈的返回*/
}

int main(int argc, char *argv[])
{
	int *p = NULL;
	int ret;
	pthread_t pthid = -1; //保存线程号

	/*p = (int **)malloc(sizeof(int *));*/


	printf("main : %lu pid = %d\n", pthread_self(), getpid());

	ret = pthread_create(&pthid, NULL, hello, NULL);
	if (ret != 0)
	{
		return -1;
	}

	//等待对应线程的退出
	pthread_join(pthid, (void **)&p);

	printf("==============\n");
	printf("p : %p\n", p);
	printf("*p : %d\n", *p);



	return 0;//表示进程结束
}
