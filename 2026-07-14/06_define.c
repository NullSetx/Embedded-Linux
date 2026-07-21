#include <stdio.h>
#include <stdarg.h>
#include <string.h>
#include <stdlib.h>

#define PI 3.14
#define R 2
//#define S PI * R * r
#define S(r) PI * r * r
#define ADD(a, b) a + b

float area(int r)
{
	return PI * r * r;
}
int main(void)
{
	int a;
	printf("input r : ");
	scanf("%d", &a);

	printf("PI : %f\n", PI);
	printf("S : %f\n", S(a));
	printf("area : %f\n", area(a));
	printf("add : %d\n", ADD(2, 3));
	return 0;
}
