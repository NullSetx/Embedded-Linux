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

#define MAX 1
int ee = 5566;

void * func(void *data)
{
	int i = 0;
	printf("pthid : %lu pid : %d ppid : %d\n", 
		pthread_self(), getpid(), getppid());
	int e = 1122;	

	if (fork() == 0)
	{
		printf("pthid : %lu pid : %d  ppid : %d\n", 
			pthread_self(), getpid(), getppid());
		e = 3344;	
		exit(0);
	}
	sleep(1);
	printf("e: %d\n", e);
	pthread_exit(NULL);

}
int main(int argc, char *argv[])
{
	int i;
	pthread_t pthid[MAX];

	for (i = 0; i < MAX; i++)
	{
		pthread_create(&pthid[i], NULL, func, NULL);
	}


	for (i = 0; i < MAX; i++)
	{
		pthread_join(pthid[i], NULL);
	}

	return 0;
}
