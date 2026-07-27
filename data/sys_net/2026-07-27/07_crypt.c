#define _XOPEN_SOURCE
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
	char *passwd = NULL;
	char key[64];
	char salt[64];
	char tmp[128];

	sp = getspnam(argv[1]);
	ERRP(NULL == sp, getspname, goto ERR1);

	printf("sp->sp_pwdp : %s\n", sp->sp_pwdp);
	
	strcpy(tmp, sp->sp_pwdp);

	*(strrchr(tmp, '$') + 1) = '\0';
	strcpy(salt, tmp);

	/*printf("salt : %s\n", salt);*/
	GETLINES("input key : ", key);
	passwd = crypt(key, salt);
	printf("passwd : %s\n", passwd);

	if (strcmp(sp->sp_pwdp, passwd) == 0)
	{
		printf("login ok!\n");
	}
	else
	{
		printf("passwd input error!\n");
	}
	return 0;
ERR1:
	return -1;
}
