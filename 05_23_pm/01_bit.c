#include <stdio.h>
#include <stdarg.h>
#include <string.h>

void binary(int num)
{
	int i;

	for (i = 31; i >= 0; i--)
	{
		if ((i + 1) % 4 == 0)
			putchar(' ');
		printf("%d", (num >> i) & 1);

	}
	putchar(10);
}


int main(void)
{
	int num;

	printf("input number : ");
	scanf("%d", &num);

	printf("num : %d\n", num);

	binary(num);

    /*
	 *num &= ~1;
	 *num &= ~(1 << 1);
	 *num &= ~(1 << 2);
	 *num &= ~(1 << 4);
     */
	//置零	
	num &= ~(1 | 1 << 1 | 1 << 2 | 1 << 4);
	num |= (1 << 7 | 1 << 8 | 1 << 9 | 1 << 11);
	//
	binary(num);

	return 0;
}
