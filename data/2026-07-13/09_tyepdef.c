#include <stdio.h>
#include <stdarg.h>
#include <string.h>
#include <stdlib.h>
#include <math.h>

//重命名 为了跨平台
/*typedef long_64 long;*/
typedef int INT;

//如果在函数指针前面添加typedef , 则这个变量名变成类型名
typedef double (FUNC)(double ,double);//函数指针变量

void print(FUNC *p, double a, double b)
{
	printf("result : %f\n", p(a, b));
}


int main(void)
{
	INT a = 10;
	int b = 20;
	
	print(pow, 5.0, 3.0);
	/*printf("a : %d\n", a);;*/

	return 0;
}
