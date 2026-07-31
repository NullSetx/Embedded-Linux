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
void *hello(void *data)
{
	printf("hello : %lu pid = %d\n", pthread_self(), getpid());

/*
 *    struct cls_t *p = (struct cls_t *)data;
 *
 *    printf("p : %d name\n", p);
 */

	/*printf("hello==========>\n");*/
	/*printf("data : %d\n", (int *)data) ;*/
	/*(int *)data = 3344;*/

	return NULL; //表示堆栈的返回
}

int main(int argc, char *argv[])
{
	
	int ret;
	pthread_t pthid = -1; //保存线程号
	int a = 1122;
	
	struct cls_t cls = {123, "tom"};
	//1 访问学生信息，不能修改学生信息
	//2 可以修改学生信息
	//3 struct cls_t *stu = NULL; //线程申请空间，main就可以初始化
	//


	printf("main : %lu pid = %d\n", pthread_self(), getpid());

	//对结构体普通变量, 不可以强制转换成指针类型
	ret = pthread_create(&pthid, NULL, hello, (void *)cls.a);

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
