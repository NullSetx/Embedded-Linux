#include <stdio.h>
#include <stdarg.h>
#include <string.h>
#include <stdlib.h>


//函数声明
//如果调用函数写在实现前面，则需做函数声明

void world(void);


//自定义函数
//函数实现
void hello(void)
{
	printf("this is my hello func!\n");
	world();
	/*main();*/
}
void world(void)
{
	printf("this is my world func!\n");
}

//主函数 入口函数
int main(void)
{
	//调用库函数
	printf("hello world!\n");//库函数

	//调用自定义
	hello();
	world();

	return 0;
}
