#include <stdio.h>
#include <stdarg.h>
#include <string.h>
#include <stdlib.h>

int main(void)
{
	int ret;
	char key[8];

	//
	//计算机识别按键的唯一表示是键值
	//
	system("stty -echo -icanon");
	while (1)
	{
		ret = read(0, key, sizeof(key));
		if (ret == -1)
		{
			return -1;
		}
		else if (ret == 1)
		{
			printf("%d ", key[0]);
		}
		else if (ret == 2)
		{
			printf("%d %d ", key[0], key[1]);
		}
		else if (ret == 3)
		{
			printf("%d %d %d ", key[0], key[1], key[2]);
		}
		fflush(NULL);

		memset(key, 0, sizeof(key));
	}

	system("stty echo icanon");
	return 0;
}
