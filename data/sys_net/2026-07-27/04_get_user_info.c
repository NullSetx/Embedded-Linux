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

int main(int argc, char *argv[])
{
	struct passwd *pw = NULL;

	pw = getpwuid(atoi(argv[1]));
	ERRP(NULL == pw, getpwuid, goto ERR1);

	printf("name : %s uid : %d shell : %s\n",
		pw->pw_name, pw->pw_uid, pw->pw_shell);

	printf("====================\n");
	while (1)
	{
		pw = getpwent();
		if (NULL == pw)
			break;
		printf("name : %s uid : %d shell : %s\n",
			pw->pw_name, pw->pw_uid, pw->pw_shell);
	}
	setpwent();
	printf("======second==============\n");
	while (1)
	{
		pw = getpwent();
		if (NULL == pw)
			break;
		printf("name : %s uid : %d shell : %s\n",
			pw->pw_name, pw->pw_uid, pw->pw_shell);
	}
	endpwent();
	return 0;
ERR1:
	return -1;
}
