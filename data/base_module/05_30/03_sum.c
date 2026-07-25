#include <stdio.h>
#include <stdarg.h>
#include <string.h>
#include <stdlib.h>

int main(void)
{
	int i, sum = 0;

	i = 1;//init
	loop:
		sum += i;//body
		i++; //add | sub
	if (i <= 100)// con
		goto loop;

	printf("1 + 2 + 3 + ... + 100 = %d\n", sum);


	return 0;
}
