#include <stdio.h>
#include <stdarg.h>
#include <string.h>
#include <stdlib.h>
#include <share.h>

int main(int argc, char *argv[])
{
	FILE *fp = NULL;
	char buf[1024];
	char *p = NULL;
	int line = 0;
	char *s = NULL;
	char tmp[128];

	/*printf("argc : %d\n", argc);*/
	ERRP(argc != 3, format : cmd + key + filename, goto ERR1);

	/*printf("format : cmd + key + filename\n");*/
	fp = fopen(argv[2], "r");
	ERRP(NULL == fp, fopen, goto ERR1);

	while (1)
	{
		line++;
		p = fgets(buf, sizeof(buf), fp);
		if (p == NULL)
		{
			break;
		}
		
		if (strstr(p, argv[1]) != NULL)
		{
			printf("%d : ", line);
			while ((s = strstr(p, argv[1])) != NULL)
			{
				memset(tmp, 0, sizeof(tmp));
				memmove(tmp, p, s - p);
				printf("%s", tmp);
				printf("\033[31m%s\033[0m", argv[1]);
				p = s + strlen(argv[1]);

			}
			printf("%s", p);
			/*printf("%d : %s\n", line, buf);*/
		}	
	}
	fclose(fp);
	return 0;
ERR1:
	return -1;
}
