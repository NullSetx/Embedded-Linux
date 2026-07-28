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

void test(void)
{
	printf("6 => hello world!\n");
}

void hello(void)
{
	printf("hello!\n");
}

void world(void)
{
	printf("world!\n");
}
int main(int argc, char *argv[])
{
	printf("main start ...\n");

	//早上10点借

	//下班6点
	atexit(test);
	atexit(hello);
	atexit(world);

	printf("main end ...\n");
	//晚上10点
	return 0;
}
