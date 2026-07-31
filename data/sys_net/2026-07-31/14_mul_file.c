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
//extern semid;
//定义互斥锁变量
/*pthread_mutex_t mutex;*/
pthread_mutex_t mutex = PTHREAD_MUTEX_INITIALIZER;



void * func(void *data)
{
	int fd = (int)data;

	char buf[128];
	int i = 0;

	//加锁
	/*lock(semid, 0);*/
	pthread_mutex_lock(&mutex);
	/*pthread_mutex_lock(&mutex);*/

	while (1)
	{
		if (i == 1000)
		{
			
			/*unlock(semid, 0);*/
			pthread_mutex_unlock(&mutex);
			pthread_exit(NULL);
		}

		snprintf(buf, sizeof(buf), "pthid : %lu pid : %d line : %d\n", 
		pthread_self(), getpid(), i);

		write(fd, buf, strlen(buf));

		i++;
	}
	//解锁
	/*unlock(semid, 0);*/
	pthread_mutex_unlock(&mutex);
	
	pthread_exit(NULL);
}
int main(int argc, char *argv[])
{
	int i;
	pthread_t pthid[MAX];
	
	int fd;

	//init_sem();
	//初始化互斥锁
	/*ERRP(pthread_mutex_init(&mutex, NULL) != 0, init false, goto ERR1);*/


	fd = creat("./test", 0666);
	ERRP(fd == -1, creat, goto ERR1);

	for (i = 0; i < MAX; i++)
	{
		pthread_create(&pthid[i], NULL, func, (void *)fd);
	}


	for (i = 0; i < MAX; i++)
	{
		pthread_join(pthid[i], NULL);
	}

	//锁的销毁
	/*pthread_mutex_destroy(&mutex);*/


	close(fd);
	return 0;
ERR1:
	return -1;
}
