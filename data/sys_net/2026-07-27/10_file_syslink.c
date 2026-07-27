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
	int ret;
	char buf[128] = {};

	ret = readlink(argv[1], buf, sizeof(buf));
	ERRP(ret == -1, readlink, goto ERR1);
	if (ret == -1)
	{
		printf("%s no syslink!\n", argv[1]);
	}
	else
	{
		printf("%s -> %s\n", argv[1], buf);
	}


	return 0;
ERR1:
	return -1;
}
