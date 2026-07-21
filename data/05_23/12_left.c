#include <stdio.h>
#include <stdarg.h>
#include <string.h>


//把十进制转换成二进制
void binary(int num)
{
	int i;

	for (i = 31; i >= 0; i--)
	{
		if ((i  + 1) % 4 == 0)
			putchar(' ');
		printf("%d", (num >> i) & 1);
	}
	putchar(10);
}

int main(void)
{
	int a = 4543653;
	
	binary(a);
	binary(a >> 24);

    /*
	 *printf("a  : %d\n", a );
	 *printf("a << 24 : %d\n", a << 24);
     */
	return 0;
}
