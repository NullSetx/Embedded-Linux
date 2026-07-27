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

int main(int argc, char **argv)// char *argv[]
{
	int i = 0;
	struct group * gr = NULL;

	gr = getgrnam(argv[1]);

	while (1)
	{
		if (gr->gr_mem[i] == NULL)
		{
			break;
		}
		printf("%s\n", gr->gr_mem[i++]);
	}	
	return 0;
}
