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
	FILE *fp = NULL;
	char buf[1024];
	char *ret;


	fp = fopen(argv[1], "r");

	while (1)
	{
		memset(buf, 0, sizeof(buf));
		ret = fgets(buf, sizeof(buf), fp);
		/*ret = fread(buf, sizeof(char), sizeof(buf), fp);*/
		if (ret == NULL)
		{
			break;
		}
		/*printf("%s\n", buf);*/
        /*
		 *printf("%d\n", atoi(strchr(buf, ':') + 3));
		 *memset(buf, 0, sizeof(buf));
         */

		if (atoi(strchr(strchr(buf, ':') + 1, ':') + 1) == atoi(argv[2])) 
		{
			*(strchr(buf, ':')) = '\0';

			printf("%s\n", buf);

		}	
	}
	return 0;
}
