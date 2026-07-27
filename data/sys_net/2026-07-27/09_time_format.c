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

int main(int argc, char *argv[])
{
	time_t t, ti;
	struct tm *tm = NULL;
	char buf[1024] = {};


	t = time(NULL);
	tm = localtime(&t);

	strftime(buf, sizeof(buf), "%Y/%m/%d(%D) %H:%M:%S", tm);

	printf("buf : %s\n", buf);
	return 0;
}
