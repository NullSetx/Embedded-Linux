#include <stdio.h>
#include <stdarg.h>
#include <string.h>
#include <stdlib.h>

int main(void)
{
	int arr[2][3][2][4][3][2];

	sizeof(arr[0][0][0])//大小 16 4 * 3 * 2 * 4 => 96
	sizeof(&arr[0][0][0])//大小 44
	arr[0][0][0] + 1 => // 8  2 * 3 * 4 => 24
	&arr[0][0][0] + 1 => // 24 96
	return 0;
}
