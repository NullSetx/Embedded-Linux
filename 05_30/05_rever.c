#include <stdio.h>
#include <stdarg.h>
#include <string.h>
#include <stdlib.h>

int main(void)
{
	int i, j, num, tmp;
	int len = 0;
	int t = 1;
	int h, l;

	printf("input number : ");
	scanf("%d", &num);

	//求数据有效位数
	tmp = num;
	while (num)
	{
		num /= 10;
		len++;
	}
	num = tmp;
	printf("len : %d\n", len);

	
	for (j = 0; j < len / 2; j++)
	{
		for (i = 0, t = 1; i < len - 1 - j; i++, t *= 10)
			;

		h = num / t % 10;
		for (i = 0, t = 1; i < j; i++, t *= 10)
			;
		l = num / t % 10;

		if (h != l)
		{
			printf("%d不是回文数!\n", num);
			return -1;
		}
	}
	
	printf("%d 是回文数!\n", num);
	return 0;
}
