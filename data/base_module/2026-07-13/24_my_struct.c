#include <stdio.h>
#include <stdarg.h>
#include <string.h>
#include <stdlib.h>

struct cls_t{
	char name[64];
	int age;

	//结构不可定义自己结构体非指针变量
	/*struct cls_t cls;*/
	struct cls_t *cls;
};

int main(void)
{
	struct cls_t cls = {"tom", 18, NULL};

	cls.cls = &cls;

	printf("name : %s\n", cls.name);
	printf("name : %s\n", cls.cls->name);
	printf("name : %s\n", cls.cls->cls->cls->cls->cls->name);
	return 0;
}
