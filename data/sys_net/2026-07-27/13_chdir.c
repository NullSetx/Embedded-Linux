#define _GNU_SOURCE
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
	/*char *p;*/
	char buf[128];

	/*size_t;*/

	printf("pwd : %s\n", get_current_dir_name());
	ret = chdir("..");
	ERRP(-1 == ret, chdir, goto ERR1);

	printf("pwd : %s\n", get_current_dir_name());

	printf("======================\n");
	printf("pwd : %s\n", getcwd(buf, sizeof(buf)));
	printf("pwd : %s\n", getwd(buf));
	printf("buf : %s\n", buf);
	return 0;
ERR1:
	return -1;
}
