#include <stdio.h>
#include <stdarg.h>
#include <string.h>

int main(void)
{
	int i, j;
	int sum = 0;

	i = 2;
	do{
		sum += i;
		i++, i++;
	}while(i <= 100);

	printf("sum : %d\n", sum);


	i = 0;
	do{
		j = 0;
		do{
			if (i == 0 || i == 1 || i == 9)
			{
				printf("* ");
			}
			else
			{
				if (j == 0 || j == i)
				{
					printf("* ");
				}
				else
				{
					printf("  ");
				}	
			}
			j++;
		}while (j <= i);

		printf("\n");
		i++;
	}while (i < 10);


	return 0;
}
