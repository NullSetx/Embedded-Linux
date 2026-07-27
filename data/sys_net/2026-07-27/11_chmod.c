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

int main(int argc, char *argv[])
{
	int ret;

	//0777 第一个0表示八进制
	/*ret = chmod(argv[1], 0777);*/
	/*ret = chmod(argv[1], S_IRUSR | S_IWUSR | S_IXUSR | S_IRGRP | S_IWGRP | S_IXGRP);*/
	ret = chmod(argv[1], S_IRWXU | S_IRWXG | S_IRWXdO);
	ERRP(ret == -1, chmod, goto ERR1);

	

	return 0;
ERR1:	
	return -1;
}
