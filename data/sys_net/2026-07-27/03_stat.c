#include <stdio.h>
#include <stdarg.h>
#include <string.h>
#include <stdlib.h>
#include <share.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>

int main(int argc, char *argv[])
{
	int ret;
	struct stat s;
	char type[] = " pc d b - l s";
	char *mode[] = {"---", "--x", "-w-", "-wx", "r--", "r-x", "rw-", "rwx"};

	ret = stat(argv[1], &s);
	/*s.st_mode;*/
	printf("%c%s%s%s\n", type[(s.st_mode & S_IFMT) >> 12], mode[(s.st_mode & S_IRWXU) >> 6], mode[(s.st_mode & S_IRWXG) >> 3], mode[s.st_mode & S_IRWXO]);
	return 0;
}
