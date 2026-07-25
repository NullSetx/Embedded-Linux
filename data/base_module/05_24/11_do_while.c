#include <stdio.h>
#include <stdarg.h>
#include <string.h>

int main(void)
{
	int i, j;

	printf("do_while : ");
	i = 11;
	do{
		printf("%d ", i);
		i++;
	}while(i < 10);
	putchar(10);


	
	printf("while : ");
	i = 11;
	while (i < 10)
	{
		printf("%d ", i);
		i++;
	}
	putchar(10);

	printf("======================\n");
	
	i = 0;
	do{
		j = 0;
		while (j <= i)
		{
			printf("* ");
			j++;
		}
		printf("\n");
		i++;
	}while (i < 5);




	return 0;
}
