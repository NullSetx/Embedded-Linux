#include <stdio.h>
#include <stdarg.h>
#include <string.h>
#include <stdlib.h>

int sum(int num)
{
	if (num == 1)
		return 1;

	return sum(num - 1) + num;	
}

void print(int num)
{
	int i;
	for (i = 0; i < num; i++)
	{
		printf("* ");
	}
}
void print_tri(int line)
{
	if (line == 0)
		return ;

	print_tri(line - 1);	
	print(line);
	printf("\n");
}
int main(void)
{
	printf("sum : %d\n", sum(100));

	print_tri(9);

	return 0;
}
