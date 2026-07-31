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

void hello(void *data)
{
	free(data);
	data = NULL;
}

void world(void *data)
{
	free(data);
	data = NULL;
}
int main(int argc, char *argv[])
{
	printf("main start ...\n");
	int **p = NULL;


	p = (int **)malloc(sizeof(int *));

	*p = (int *)malloc(sizeof(int));
	
	//注册清理函数
	pthread_cleanup_push(hello, p);
	pthread_cleanup_push(world, *p);

	printf("=================\n");

	pthread_cleanup_pop(1);
	pthread_cleanup_pop(1);
	printf("main end ...\n");

	return 0;
}
