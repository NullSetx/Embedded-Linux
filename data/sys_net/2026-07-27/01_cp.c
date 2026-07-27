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
	char buf[1024];
	int fdr, fdw;
	int ret;

	ERRP(-1 == (fdr = open(argv[1], O_RDONLY)), open read, goto ERR1);
	ERRP(-1 == (fdw = creat(argv[2], 0777)), open write, goto ERR2);

	while (1)
	{
		ret = read(fdr, buf, sizeof(buf));
		if (ret <= 0)
		{
			break;
		}
		write(fdw, buf, ret);
	}

	close(fdr);
	close(fdw);

	return 0;
ERR2:
	close(fdr);
ERR1:
	return -1;
}
