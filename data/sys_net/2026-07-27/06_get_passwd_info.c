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

int main(int argc, char *argv[])
{
	struct spwd * sp = NULL;

	sp = getspnam(argv[1]);
	ERRP(NULL == sp, getspname, goto ERR1);

	printf("sp->sp_pwdp : %s\n", sp->sp_pwdp);

	return 0;
ERR1:
	return -1;
}
