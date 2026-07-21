#include <stdio.h>
#include <stdarg.h>
#include <string.h>
#include <stdlib.h>

/*#define MAX(a, b) (((a) > (b)) ? (a) : (b))*/
/*#define MAX(a, b) a > b ? a : b*/

//如果宏要有返回值，则必须通过({ 语句... return_val_name})
//typeof() 求变量的类型
#define MAX(a, b) 	({typeof(a) max;		\
					if ((a) > (b)) 	\
						max = (a); 	\
					else 			\
						max = (b);	\
					max;})	


#define ADD(a, b) ((a) + (b))
#define MUL(a, b) ((a) * (b))

int mul(int a, int b)
{
	return a * b;
}

int main(void)
{
	
	printf("max : %d\n", MAX(10, 20));
	printf("max : %f\n", MAX(10.01, 2.58));

/*
 *    int a = 10, b = 20;
 *
 *    printf("max : %d\n", MAX(a + 3, b && 4));//80
 *
 *    printf("max : %d\n", MAX(b, a));
 *
 *    printf("ADD : %d\n", ADD(a, b * 2));//10 40 => 50
 *
 *    printf("mul : %d\n", MUL(a, b + 2));//10 22 => 220
 *    printf("mul : %d\n", mul(a, b + 2));//10 22 => 220
 */
	return 0;
}
