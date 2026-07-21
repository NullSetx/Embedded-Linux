#include <stdio.h>
#include <stdarg.h>
#include <string.h>

int main(void)
{
	int count = 0;

	loop:
		if (count == 5)
		{
			goto out;
		}
		printf("hello!\n");
		count++;
	goto loop;

	out:
	printf("world!\n");

    /*
	 *loop:
	 *    printf("hello!\n");
     */
	return 0;
}
