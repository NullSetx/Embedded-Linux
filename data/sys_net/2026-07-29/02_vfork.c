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

int main(int argc, char *argv[])
{
	int count = 100;

	if (vfork() == 0)
	{
		sleep(1);
		count = 200;
		printf("child => count : %d\n", count);
		return 0;
		/*exit(0);*/
	}

	/*wait(NULL);*/
	printf("parent! count = %d\n", count);

	return 0;
}
