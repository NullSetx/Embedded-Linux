#include <stdio.h>
#include <stdarg.h>
#include <string.h>
#include <stdlib.h>

// 0 -> 0 1-> 1 ....  10=>a 11=>b ...
//"0123456789abcdefghijk"
void binary(int num, int bit)
{
	if (num == 0)
		return ;
	
	binary(num / bit, bit);
	putchar("0123456789abcdefghijklmn"[num % bit]);
    /*
	 *if (num % bit == 10)
	 *{
	 *    putchar('a');
	 *}
	 *else if (num % bit == 11)
	 *{
	 *    putchar('b');
	 *}
	 *else if (num % bit == 12)
	 *{
	 *    putchar('c');
	 *}
	 *else if (num % bit == 13)
	 *{
	 *    putchar('d');
	 *}
	 *else if (num % bit == 14)
	 *{
	 *    putchar('e');
	 *}
	 *else if (num % bit == 15)
	 *{
	 *    putchar('f');
	 *}
	 *else
	 *    printf("%d", num % bit);
     */
}

int main(void)
{
	int num, bit;

	printf("input number and bit : ");
	scanf("%d%d", &num, &bit);
	binary(num, bit);
	putchar(10);

	return 0;
}
