#include <stdio.h>
#include <stdarg.h>
#include <string.h>
#include <stdlib.h>

struct op_t{
	unsigned int a : 2;//-2147483648 ~ 2147483647
	char ch3:7;
	char ch;
	char ch1;
	char ch2;
	//表示只用了32位中的2位 
	//11
};
	
int main(void)
{
	/*int a :2;*/

	struct op_t op;


	/*op.a = 2147483647;*/
	op.a = 3;
	printf("op.a : %d\n", op.a);
	printf("sizeof(struct op_t) : %d\n", sizeof(struct op_t));
	return 0;
}
