#include <stdio.h>
#include <stdarg.h>
#include <string.h>
#include <stdlib.h>


//结构体大小，32位系统默认是最大最齐是4个字节
//如果结构体成员大小小于4个字节，则以最大成员空间大小对齐。

#pragma pack(1)
struct op_t{
	char name;
	int a;//4
    /*
	 *char ch;//1
	 *char ch2;
	 *short s;//2
     */

};
#pragma pack(0) //恢复默认状态

struct op_tt{
	char name;
	int a;//4

};
int main(void)
{
	struct op_t op;

    /*
	 *printf("&op.ch : %p\n", &op.ch);
	 *printf("&op.a : %p\n", &op.a);
     */
	printf("sizeof(char) : %d\n", sizeof(char));
	printf("sizeof(struct op_t) : %d\n", sizeof(struct op_t));
	printf("sizeof(struct op_tt) : %d\n", sizeof(struct op_tt));
	return 0;
}
