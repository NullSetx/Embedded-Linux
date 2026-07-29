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

void didi(int sig)
{
	printf("hello! time : %d\n", time(NULL));
}
void world(int sig)
{
	printf("world! time : %d\n", time(NULL));
}

int main(int argc, char *argv[])
{
	int ret;
	struct itimerval it;
	struct itimerval it1;

	//2 捕捉闹钟信号
	ERRP(signal(14, didi) == SIG_ERR, signal, goto ERR1);
	ERRP(signal(26, world) == SIG_ERR, signal, goto ERR1);

	//1 设定定时器  机器时间
	//第一次执行时间
	it.it_value.tv_sec = 3;
	it.it_value.tv_usec = 100;
	//循环时间
	it.it_interval.tv_sec = 1;
	it.it_interval.tv_usec = 100;

	ret = setitimer(ITIMER_REAL, &it, NULL);
	ERRP(ret == -1, setitimer, goto ERR1);

	//1 设定定时器  机器时间
	//第一次执行时间
	it1.it_value.tv_sec = 3;
	it1.it_value.tv_usec = 100;
	//循环时间
	it1.it_interval.tv_sec = 2;
	it1.it_interval.tv_usec = 100;

	ret = setitimer(ITIMER_VIRTUAL, &it1, NULL);
	ERRP(ret == -1, setitimer, goto ERR1);


	/*getchar();//睡眠方式等待信号执行*/

	while (1)
		;

	return 0;
ERR1:
	return -1;
}
