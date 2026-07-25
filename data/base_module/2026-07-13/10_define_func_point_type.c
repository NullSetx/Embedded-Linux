#include <stdio.h>
#include <stdarg.h>
#include <string.h>
#include <stdlib.h>

//定义函数指针类型
typedef int (FUNC)(int, int);


int add(int a, int b)
{
	return a + b;
}
int sub(int a, int b)
{
	return a - b;
}
int mul(int a, int b)
{
	return a * b;
}
int dev(int a, int b)
{
	return a / b;
}
int mod(int a, int b)
{
	return a % b;
}
int my_pow(int a, int b)
{
	int tmp = 1;
	while (b--)
	{
		tmp *= a;
	}
	return tmp;	
}

int count_match(FUNC *func, int a, int b)
{
	
	return  func(a, b);
}

int main(void)
{
	int i, count = 0, j;
	//函数指针数组
	FUNC *p[6] = {add, sub, mul, dev, mod, my_pow};

	printf("sizeof(p) : %d\n", sizeof(p));

	for (i = 0; i < 6; i++)
	{
		for (j = 0; j < 6; j++)
		{
			/*printf("%d\n", p[j](p[i](5, 3), 2));*/
			if (p[j](p[i](5, 3), 2) == 4)
				count++;
		}
	}
	printf("count : %d\n", count);

/*
 *    int (*p1)(int, int) = add;
 *    int (*p2)(int, int) = sub;
 *    int (*p3)(int, int) = mul;
 *    int (*p4)(int, int) = dev;
 *    int (*p5)(int, int) = mod;
 *    int (*p6)(int, int) = my_pow;
 *
 *    count_match(p1, 5, 3)
 *        {
 *            ( , 3);
 *            ( , 3);
 *            ( , 3);
 *            ( , 3);
 *            ( , 3);
 *
 *
 *        }
 *    count_match(p2, 5, 3)
 *    count_match(p3, 5, 3)
 *    count_match(p4, 5, 3)
 *    count_match(p5, 5, 3)
 *    count_match(p6, 5, 3)
 */
	return 0;
}
