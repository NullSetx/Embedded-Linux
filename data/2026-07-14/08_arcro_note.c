#include <stdio.h>
#include <stdarg.h>
#include <string.h>
#include <stdlib.h>

//1 宏必须是一行来实现，如果有多行，则必须在每一行的结尾添加\(续行符)
//2 宏参数是没有类型的，参数必须添加()
//3 宏有返回值 {()}
//4 宏和函数区别
//5 宏是纯文本的替换
//
#define ADD(a, b) ((a) + (b))
#define MAX(a, b) (((a) > (b)) ? (a) : (b))

#define GETLINES(info, buf)				\
	do{									\
		printf(info);						\
		fgets(buf, sizeof(buf), stdin);		\
		if (buf[strlen(buf) - 1] == '\n')	\
			buf[strlen(buf) - 1] = '\0';	\
	}while (0)

int main(void)
{
	int max;
	int a = 10, b = 20;
	char buf[128];
	char name[64];

	GETLINES("input user name : ", name);

	printf("name : %s\n", name);

/*
 *    if (1)
 *    {
 *        GETLINES("input string : ", buf);
 *    }	
 *    else
 *        printf("test!\n");
 *
 *    printf("buf : %s\n", buf);
 */
    /*
	 *printf("add : %d\n", ADD(10, 20));	
	 *printf("add : %d\n", ADD(10, 20) * 2);	
	 *
	 *max = MAX(a, b);
	 *printf("max : %d\n", max);
     */
	return 0;
}
