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

//实现加密解密算法

unsigned char my_crypt(unsigned char old, unsigned char *new)
{
	if (new == NULL)
	{
		return (((old & 0xf0) >> 4) | (old & 0xf) << 4);
	}
	else
	{
		*new = (((old & 0xf0) >> 4) | (old & 0xf) << 4);
	}	
}


int main(int argc, char *argv[])
{
	int i;
	unsigned char buf[128];
	unsigned char tmp[128] = {};
	unsigned char s[128] = {};

	GETLINES("input string : ", buf);

	printf("buf : %s\n", buf);

	for (i = 0; i < strlen(buf); i++)
	{
		tmp[i] = my_crypt(buf[i], NULL);
	}
	printf("tmp : %s\n", tmp);

	//解密
	for (i = 0; i < strlen(tmp); i++)
	{
		s[i] = my_crypt(tmp[i], NULL);
	}
	printf("s : %s\n", s);
	
	return 0;
}
