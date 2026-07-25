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
	mode_t m;

	ret = lstat(argv[1], &s);
	ERRP(ret == -1, stat, goto ERR1);

	PRI_O(s.st_mode);    /* protection */
	m = s.st_mode;

	if (S_ISREG(m))
	{
		putchar('-');
	}
	else if (S_ISDIR(m))
	{
		putchar('d');
	}
	else if (S_ISCHR(m))
	{
		putchar('c');
	}
	else if (S_ISBLK(m))
	{
		putchar('b');
	}
	else if (S_ISFIFO(m))
	{
		putchar('p');
	}
	else if (S_ISLNK(m))
	{
		putchar('l');
	}
	else if (S_ISSOCK(m))
	{
		putchar('s');
	}

//	owner
	if ((m & S_IRUSR) == S_IRUSR)
	{
		putchar('r');
	}
	else
	{
		putchar('-');
	}
	if ((m & S_IWUSR) == S_IWUSR)
	{
		putchar('w');
	}
	else
	{
		putchar('-');
	}
	if ((m & S_IXUSR) == S_IXUSR)
	{
		putchar('x');
	}
	else
	{
		putchar('-');
	}

	putchar(10);
	return 0;
ERR1:
	return -1;
}
