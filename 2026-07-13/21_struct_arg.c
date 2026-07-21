#include <stdio.h>
#include <stdarg.h>
#include <string.h>
#include <stdlib.h>

//定义学生结构体
struct cls_t{
	char name[64];
	int age;
	float sum;
	//......
};

void access(struct cls_t cls)
{
	printf("access => &cls : %p\n", &cls);
	printf("name : %s\n", cls.name);
	strcpy(cls.name, "jim");
	printf("name : %s\n", cls.name);

}

void modifier(struct cls_t *cls)
{
	printf("name : %s\n", cls->name);
	strcpy(cls->name, "jim");
	printf("name : %s\n", cls->name);
	
}
int main(void)
{
	//定义学生结构体变量 定义并初始化
	struct cls_t cls = {"tom", 18, 99.88};

	printf("main => &cls : %p\n", &cls);
	/*access(cls);*/

	modifier(&cls);


	printf("main => name : %s\n", cls.name);

	return 0;
}
