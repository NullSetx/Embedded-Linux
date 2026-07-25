#include <stdio.h>
#include <stdarg.h>
#include <string.h>
#include <stdlib.h>

int *p = NULL;
void test(void)
{
	//作用域：就是当前的变量在某个范围内有效
	//生存周期：就是当前的变量从定义开始到消亡过程
	static int count = 0;//局部变量
	
	p = &count;

	printf("count : %d\n", count++);
	
}

//声明
/*int e;*/
/*extern int e;*/
extern e;

static void my_env(void);

int main(void)
{
    /*
	 *static   *****
	 *auto
	 *const    ****	
	 *signed
	 *unsigned
	 *extern 
	 *register ：寄存器   ***
	 *volatile : 防止优化 ***
     */
	static int a;//stack


	test();
	test();
	test();
	test();
	//
	//局部变量，位于栈中，程序启动而栈是不会初始化
	//静态变量，位于数据段(全局区)，程序启动之前就会初始化为0
	//
	//静态修饰3个作用
	//1 修饰局部变量：
	//	局部只对当前的函数有效
	//	静态局部变量是对整个函数有效  生存周期
	//2 修饰全局变量
	//	全局变量，所有的文件有效
	//	静态全局变量，只对当前的文件有效
	//3 修饰函数
	//	函数是所有的文件都可以调用
	//	静态函数只能本文件中的函数可以调用
	//
	printf("a : %d\n", a);
	printf("*p : %d\n", *p);
	/*printf("count : %d\n", count);*/
	/*printf("main : e = %d\n", e);*/
	my_env();
	return 0;
}
