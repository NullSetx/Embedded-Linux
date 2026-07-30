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

int main(int argc, char *argv[])
{
	key_t key;
	int num;

	struct stat s;

	key = ftok(argv[1], 123);
	ERRP(-1 == key, ftok, goto ERR1);

	PRI_H(key);

	stat(argv[1], &s);
	PRI_H(s.st_ino);

	num = (123 << 24) | (0x2 << 16) | (s.st_ino & 0xffff);

	if (num == key)
	{
		printf("match success!\n");
	}
	return 0;
ERR1:
	return -1;
}
