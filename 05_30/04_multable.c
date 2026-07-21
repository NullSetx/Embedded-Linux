#include <stdio.h>
#include <stdarg.h>
#include <string.h>
#include <stdlib.h>

int main(void)
{
	int i, j;

	i = 1;
	I:
		//=======================
		//嵌套列
		j = 1;
		J:
			printf("%d * %d = %2d  ", j, i, i * j);
			j++;
		if (j <= i)
			goto J;
		//======================
		printf("\n");
		i++;
	if (i < 10)
		goto I;

	return 0;
}
