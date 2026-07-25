#include <stdio.h>
#include <stdarg.h>
#include <string.h>
#include <stdlib.h>

int main(void)
{
	while (1)
	{
		while (1)
		{
			while (1)
				goto out;
		}
	}

	out:
	return 0;
}
