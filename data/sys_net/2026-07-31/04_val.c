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

int e = 1122; //DS => share
char *s = NULL;//DS
int *p = NULL;

//线程执行流
void *hello(void *data)
{
	printf("hello : %lu pid = %d\n", pthread_self(), getpid());
	e = 3344;
	printf("hello : e = %d\n", e);
	printf("hello : s : %s\n", s);//heap => share
	strcpy(s, "zhangsan");
	*p = 456;

	free(s);
	s = NULL;
	return NULL; //表示堆栈的返回
}

int main(int argc, char *argv[])
{
	int a = 123;//局部变量
	int ret;
	pthread_t pthid = -1; //保存线程号

	s = (char *)malloc(100);//heap | DS -> heap
	p = &a;//stack
	strcpy(s, "tom");

	printf("main : %lu pid = %d\n", pthread_self(), getpid());

	ret = pthread_create(&pthid, NULL, hello, NULL);
	if (ret != 0)
	{
		return -1;
	}

	sleep(1);
	printf("pthid : %lu\n", pthid);
	printf("main : e = %d\n", e);
	printf("main : s = %s\n", s);
	/*printf("main : s = %c\n", s[0]);*/
	printf("main : a = %d\n", a);


	return 0;//表示进程结束
}
