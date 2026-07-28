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

void my_tree(const char *path)
{
	int i;
	DIR *dir = NULL;
	struct dirent * d = NULL;
	static int lev = 0;

	/*printf("path : %s\n", path);*/
	dir = opendir(path);
	if (dir == NULL)
	{
		/*printf("err : %s\n", path);*/
		return ;
	}
	/*ERRP(dir == NULL, opendir, goto ERR1);*/
	chdir(path);

	while (1)
	{
		d = readdir(dir);
		if (NULL == d)
		{
			break;
		}
		if (d->d_name[0] == '.')
			continue;
		for (i = 0; i < lev; i++)
		{
			printf("|   ");
		}
		printf("|-- %s\n", d->d_name);
		if (d->d_type == 4)
		{
			lev++;
			my_tree(d->d_name);
			lev--;
		}

	}
	chdir("..");

	closedir(dir);

	return ;
ERR1:
	return ;
}

int main(int argc, char *argv[])
{
	struct stat s;

	ERRP(stat(argv[1], &s) == -1, stat, goto ERR1);

	if (S_ISDIR(s.st_mode))
	{
		my_tree(argv[1]);
	}



	return 0;
ERR1:
	return -1;
}
