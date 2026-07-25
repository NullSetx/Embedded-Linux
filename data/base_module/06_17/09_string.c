#include <stdio.h>
#include <stdarg.h>
#include <string.h>
#include <stdlib.h>

int main(void)
{
	int i,j;
    /*
	 *char name[10][10] = {{'t', 'o', 'm'},
	 *                     {'j', 'i', 'm'}, 
	 *                     {'m', 'a', 'r', 'y'}};
     */

	char name[10][10] = {"tom", "jim", "mary"};
	for (i= 0; i < 10; i++)
	{
		for (j = 0; j < 10; j++)
		{
			putchar(name[i][j]);
		}
		putchar(10);
	}

	printf("===================\n");
	strcpy(name[0], "join");

	for (i = 0; i < 3; i++)
		printf("%s\n", name[i]);
	return 0;
}
