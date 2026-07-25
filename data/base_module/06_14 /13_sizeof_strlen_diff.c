#include <stdio.h>
#include <stdarg.h>
#include <string.h>
#include <stdlib.h>

int main(void)
{
	char s1[] = "hel\0lo\0";
	char s2[] = {'h', 'e', 'l', '\0', 'l', 'o', '\0'};

	//区别
	/*
	 1 sizeof()是运算符 strlen()是函数
	 2 sizeof()是求空间大小，编译时候就会确定大小
	   strlen()是求字符串的有效长度，只有在运行的时候才会确定
	 3 sizeof()可以求任意数据类型的大小
	   strlen()只能求字符串的有效长度
	 4 sizeof()求空间大小的时候包含尾零
	   strlen()求字符串有效长度的时候不包含尾零。

	 
	*/
	// 6 5
	printf("sizeof(s1) : %d strlen(s1) : %d\n", sizeof(s1), strlen(s1));
	// 5 5
	printf("sizeof(s2) : %d strlen(s2) : %d\n", sizeof(s2), strlen(s2));
	return 0;
}
