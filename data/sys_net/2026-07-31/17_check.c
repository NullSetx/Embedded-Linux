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

int check_odd_even(int num)
{
	int i;
	int count = 0;

	for (i = 31; i >= 0; i--)
	{
		if ((num >> i) & 1)
			count++;
	}

	return count % 2;
}

int main(int argc, char *argv[])
{
	unsigned int num;
	
	printf("input number : ");
	scanf("%u", &num);

	if (check_odd_even(num))
	{
		printf("odd check!\n");
	}
	else
	{
		printf("even check!\n");
	}

	return 0;
}
