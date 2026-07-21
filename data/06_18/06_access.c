#include <stdio.h>
#include <stdarg.h>
#include <string.h>
#include <stdlib.h>

int main(void)
{
	int i;
	int arr[2][3] = {1,2,3,4,5,6};

	for (i = 0; i < 6; i++)
	{
		/*printf("%p => %d\n", &arr[0][0] + i, *(&arr[0][0] + i));*/
		/*printf("%p => %d\n", arr[0] + i, *(arr[0] + i));*/
		printf("%p => %d\n", arr[0] + i, arr[0][i]);
	}
	return 0;
}
