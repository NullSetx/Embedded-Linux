#include <stdio.h>
#include <stdarg.h>
#include <string.h>
#include <stdlib.h>

//实现两个数累加
int add(int a, int b) //形参
{
	printf("a : %d b : %d\n", a, b);

	return a + b;
}

int main(void)
{
	int a, b;
	int sum;

	sum = add(1, 2);//实参
	printf("sum : %d\n", sum);

	printf("input a and b : ");
	scanf("%d%d", &a, &b);

	printf("sum : %d\n", add(a, b));//实参




	return 0;
}
