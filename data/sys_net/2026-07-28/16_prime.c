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

#define NUM 10
#define MIN 3000
#define MAX 6000
#define STEP (MAX - MIN)/NUM

int count_prime(int min, int max)
{
	int i, j, count = 0;

	printf("pid : %d min : %d max : %d\n", getpid(), min, max);
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
			/*printf("%d ", i);*/
			count++;
		}
	}

	return count;
}

int main(int argc, char *argv[])
{
	int i;
	int status;
	int count = 0;

	/*printf("count : %d\n", count_prime(3000, 6000));*/

	for (i = 0; i < NUM; i++)
	{
		if(fork() == 0)
		{
			exit(count_prime(MIN + i * STEP, MIN + (i + 1) * STEP));
			/*printf("hello!\n");*/
			/*exit(0);*/
		}
	}

	for (i = 0; i < NUM; i++)
	{
		wait(&status);
		if (WIFEXITED(status))
		{
			count += WEXITSTATUS(status);
		}
	}
	printf("count : %d\n", count);
	return 0;
}
