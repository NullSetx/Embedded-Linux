#include <stdio.h>
#include <stdarg.h>
#include <string.h>

int main(void)
{
	int i, j;

	i = 1;//init
	while (i < 10)//con
	{//body
		printf("%d ", i);
		i++;//add | sub
	}
	putchar(10);
	i = 10;//init
	while (i > 0)//con
	{//body
		printf("%d ", i);
		i--;//add | sub
	}
	putchar(10);


	printf("==============\n");
	
	i = 0;
	while (i < 5)
	{
		j = 0;
		while (j < 5)
		{
			printf("* ");
			j++;
		}
		printf("\n");
		i++;
	}



	return 0;
}
