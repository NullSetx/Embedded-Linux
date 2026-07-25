#include <stdio.h>
#include <stdarg.h>
#include <string.h>
#include <stdlib.h>

//定义枚举类型
enum Color {RED, GREEN = 5, BULE};

int main(void)
{
	enum Color c = RED;
	printf("c : %d\n", c);
	printf("%d : %d : %d\n", RED, GREEN, BULE);
	return 0;
}
