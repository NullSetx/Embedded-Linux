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

int main(int argc, char *argv[])
{
	DIR *dir = NULL;
	struct dirent *d = NULL;


	dir = opendir(argv[1]);
	ERRP(NULL == dir, opendir, goto ERR1);

	while (1)
	{
		d = readdir(dir);
		if (NULL == d)
		{
			goto ERR1;
		}
		//. .. .filename
		if (d->d_name[0] == '.')
		{
			continue;
		}
		printf("inode : %d  type : %d name : %s\n", 
			d->d_ino, d->d_type, d->d_name);
	}
	closedir(dir);
	return 0;
ERR1:
	return -1;
}
