#include <stdio.h>
#include <stdarg.h>
#include <string.h>
#include <stdlib.h>

int main(void)
{
	int i;
	char s[64] = {'h', 'e', 'l', 'l', 'o'};

	char name[64] = "hello";

	printf("s : %s\n", s);

	for (i = 0; i < 5; i++)
	{
		/*printf("%c", s[i]);*/
		printf("%c", name[i]);
	}
	putchar(10);


	printf("name : %s\n", name);

	return 0;
}
