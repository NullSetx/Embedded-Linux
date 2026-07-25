#include <stdio.h>
#include <stdarg.h>
#include <string.h>
#include <stdlib.h>
#include <share.h>

#define AA 


//取消宏
//#undef AA

int main(void)
{
	#if 0
	//如果定义宏，则执行
	#ifdef AA
	printf("hello!\n");
	#endif
	#endif


	//如果定义宏，则不执行，反之，则执行
	#ifndef AA
	printf("hello!\n");
	#endif
	return 0;
}
