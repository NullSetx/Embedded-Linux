#include <stdio.h>
#include <stdarg.h>
#include <string.h>
#include <stdlib.h>

//定义函数指针类型
typedef int (FUNC)(int, int);


struct op_t{
	char ch;
	FUNC *func;
};

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


int main(void)
{
	int i, count = 0, j;
	//函数指针数组
	struct op_t p[6] = {{'+', add},
						 {'-', sub},
						 {'*', mul},
						 {'/', dev},
						 {'%', mod},
						 {'^', my_pow}};

	printf("sizeof(p) : %d\n", sizeof(p));

	for (i = 0; i < 6; i++)
	{
		for (j = 0; j < 6; j++)
		{
			if (p[j].func(p[i].func(5, 3), 2) == 4)
			{
				printf("(5 %c 3) %c 2 = 4\n", p[i].ch, p[j].ch);		
			}
		}
	}
	return 0;
}
