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

#define NUM 10
#define MIN 3000
#define MAX 6000
#define STEP (MAX - MIN) / NUM


struct op_t{
	int min;
	int max;
};

void *count_prime(void *data)
{
	int i, j, min, max;
	int *count = NULL;
	
	/*sleep(1);*/
	//malloc 申请内存空间，值是随机数
	count = (int *)malloc(sizeof(int));
	ERRP(count == NULL, malloc, goto ERR1);
	
	*count = 0;

	min = *(int *)data;
	max = min + STEP;

	for (i = min; i < max; i++)
	{
		for (j = 2; j < i; j++)
		{
			if (i % j == 0)
			{
				break;
			}
		}
		if (i == j)
		{
			(*count)++;
		}
	}

	printf("pthid : %lu min : %d *count : %d\n", 
		pthread_self(), min, *count);

	pthread_exit(count);
ERR1:
	pthread_exit(NULL);
}

int main(int argc, char *argv[])
{
	int i;
	int min[NUM];
	pthread_t pthid[NUM];
	int *p = NULL;
	int result = 0;
	

	/*printf("count : %d\n", *(int *)count_prime(NULL));*/
	#if 1
	for (i = 0; i < NUM; i++)
	{
		min[i] = MIN + i * STEP;
		pthread_create(pthid + i, NULL, count_prime, &min[i]);
	}

	for (i = 0; i < NUM; i++)
	{
		pthread_join(pthid[i], (void **)&p);
		if (p != NULL)
		{
			result += *p;
		}
		free(p);
		p = NULL;
	}
	
	printf("result : %d\n", result);
	#endif
	return 0;
}
