#include <stdio.h>
#include <stdarg.h>
#include <string.h>

int main(void)
{
	int count = 0;
	//time(NULL) : 表示从1970年1月1日到此刻总秒数
	//1 秒 = 1000 毫秒
	//1 毫秒 = 1000 微妙
	while (1)
	{
		if (count == 5)
		{
			printf("continue...\n");
			/*break;*/
			continue;
		}
		printf("hello world! %d\n", time(NULL));
		/*sleep(1);*/
		/*usleep(100000);*/
		count++;
	}
	return 0;
}
