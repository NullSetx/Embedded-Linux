#include <stdio.h>
#include <stdarg.h>
#include <string.h>

int main(void)
{
	int a = 5;
	int b = 3;

	//a+++++b;
	//a++ + ++b
	//a + ++ ++b
	//a++ ++ +b
	// 1 print执行顺序：从右到左
	// 2 前缀自加操作变量本身 后缀自加操作是临时变量
	//                   t=7   a=8     t=5
	/*printf("%d:%d:%d\n", a++, ++a, a++);//677 775 566 577 567 */
	//                  a=8      t=6     a=8
	printf("%d:%d:%d\n", ++a, a++, ++a);//776 868
	/*b = a++;*/
/*
 *    b = ++a;
 *
 *    printf("a : %d b : %d\n", a, b);
 */
	return 0;
}
