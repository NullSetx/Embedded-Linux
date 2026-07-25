#include <stdio.h>
#include <stdarg.h>
#include <string.h>
#include <stdlib.h>

int main(void)
{
	int arr[2][3][4];
	int (*p)[3][4];
	/*int (*p)[4][3] = NULL;*/
	/*int (*p)[12] = NULL;*/

	printf("p : %p p + 1 : %p\n", p, p + 1);//0x30
	p = arr;

	return 0;
}
