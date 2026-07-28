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
	printf("test!\n");
	abort();
}
int main(int argc, char *argv[])
{
	printf("hello! pid = %d\n", getpid());
	getchar();
	/*abort();*/
	/*test();*/
	printf("world!\n");

	return 0;
}
