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
	int a = 42352545, b = 3415632;

	//0000 0000 0000 0000 0000 0000 0000 0101
	//0000 0000 0000 0000 0000 0000 0000 0010
	binary(a);
	/*binary(~a);*/
	binary(b);
	binary(a ^ b);
	printf("a & b = %d\n", a & b);

	printf("======================\n");
	binary(-1);

	return 0;
}
