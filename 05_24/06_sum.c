#include <stdio.h>
#include <stdarg.h>
#include <string.h>

int main(void)
{
	int i;
	int sum = 0;

	for (i = 1; i <= 100; i++)
	{
		sum += i;
		/*printf("%d ", i);*/
	}
	
	printf("1 + 2 + 3 + ... + 100 = %d\n", sum);
	return 0;
}
