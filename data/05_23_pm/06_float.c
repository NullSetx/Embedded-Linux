#include <stdio.h>
#include <stdarg.h>
#include <string.h>

int main(void)
{
	float f;
	
	printf("input float : ");
	scanf("%f", &f);

	f = f - 83.34;
	
	//浮点数跟0比较，一定是一个范围，不能直接跟0做比较
	//浮点数默认小数点后6位数据有效
	if (f < 0.00001 && f > -0.00001)
	{
		printf("float is 0!\n");
	}
	printf("f : %f\n", f);
	printf("f : %g\n", f);


    /*
	 *if (f == 83.34)
	 *{
	 *    printf("hello!\n");
	 *}
     */

	return 0;
}
