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

int main(void)
{
	//定义学生结构体变量 定义并初始化
	struct cls_t cls = {"tom", 18, 99.88};

	//访问：. ->
	//如果结构体变量是指针变量，则访问成员通过 ->
	//如果结构体变量是非指针变量，则访问成员通过 .
	printf("name : %s\n", cls.name);
	printf("age : %d\n", cls.age);
	printf("sum : %.2f\n", cls.sum);
	
	strcpy(cls.name, "jim");

	printf("name : %s\n", (&cls)->name);

	printf("input name : ");
	fgets(cls.name, sizeof(cls.name), stdin);
	if (cls.name[strlen(cls.name) - 1] == '\n')
		cls.name[strlen(cls.name) - 1] = '\0';
	printf("name : %s\n", (&cls)->name);

	printf("input age : ");
	scanf("%d", &cls.age);
	printf("age : %d\n", cls.age);
	
	


	return 0;
}
