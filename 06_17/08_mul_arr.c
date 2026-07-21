#include <stdio.h>
#include <stdarg.h>
#include <string.h>
#include <stdlib.h>


int main(void)
{
	int i, j;
	/*int arr[2][3] = {1,3,4,5,6};*/
	int arr[2][3] = {{1,3}, {4,5,6}};

	for (i = 0; i < 2; i++)
	{
		for (j = 0; j < 3; j++)
		{
			printf("arr[%d][%d] = %d\n", i, j, arr[i][j]);
		}
	}
	return 0;
}
