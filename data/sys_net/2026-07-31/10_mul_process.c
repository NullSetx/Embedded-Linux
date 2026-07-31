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

#define MAX 10

void * func(void *data)
{
	printf("pthid : %lu pid : %d\n", pthread_self(), getpid());

	abort();//异常
	return NULL;
}
int main(int argc, char *argv[])
{
	int i;
	pthread_t pthid[MAX];

	for (i = 0; i < MAX; i++)
	{
		if (fork() == 0)
		{
			printf("hello : pid = %d\n", getpid());
			abort();
		}
		/*pthread_create(&pthid[i], NULL, func, NULL);*/
	}

	sleep(1);

	for (i = 0; i < MAX; i++)
	{
		printf("pthid[%d] : %lu\n", i, pthid[i]);
	}

	return 0;
}
