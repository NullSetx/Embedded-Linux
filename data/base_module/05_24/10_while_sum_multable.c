#include <stdio.h>
#include <stdarg.h>
#include <string.h>



int main(void)
{
	int i, j;
	//局部变量 未初始化的局部变量值是随机数
	int sum = 0;

	printf("sum : %d\n", sum);
	i = 1;
	while (i < 100)
	{
        /*
		 *if (i % 2 != 0)//判断奇数
		 *{
		 *    sum += i;
		 *}	
         */
		sum += i;
		i++, i++;//i += 2
	}
	printf("1 + 3 + 5 + ... + 99 = %d\n", sum);

	printf("===================\n");
	i = 1;
	while (i < 10)
	{
		//==================
		j = 1;
		while (j <= i)
		{
			printf("%d * %d = %2d  ", j, i, i * j);
			j++;
		}
		//==================
		printf("\n");
		i++;
	}
	return 0;
}
