#include <stdio.h>
#include <stdarg.h>
#include <string.h>
#include <stdlib.h>

//定义共用体类型
union op_t{
	char ch;
	int a;
};

int main(void)
{
	union op_t op = {};
	//空间大小由成员中最大的成员所占的空间来决定
	printf("sizeof(union op_t) = %d\n", sizeof(union op_t));

	printf("op.a : %d\n", op.a);
	op.ch = 'A';
	printf("op.a : %d\n", op.a);

	printf("&op.ch : %p\n", &op.ch);
	printf("&op.a : %p\n", &op.a);

	return 0;
}
