#include <stdio.h>
#include <stdarg.h>
#include <string.h>
#include <stdlib.h>

int main(void)
{
	
	printf("max : %d\n", RAND_MAX);
	while (1)
	{
		//随机小写字母
		/*putchar(rand() % 26 + 'a');*/
		printf("%.2f ",(rand() / (float)RAND_MAX) * 100);
		usleep(100000);
		fflush(NULL);
	}
	return 0;
}
