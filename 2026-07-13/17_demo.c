#include <stdio.h>
#include <stdarg.h>
#include <string.h>
#include <stdlib.h>

//定义学生结构体
struct cls_t{
	int age;
	float sum;
	char *name;
	//......
};

int main(void)
{
	//定义学生结构体变量 定义并初始化
	struct cls_t *p = NULL;

	//外部接受数据保存在p结构体中
	//
	p = (struct cls_t *)malloc(sizeof(struct cls_t));
	if (p == NULL)
	{
		return -1;
	}

	p->name = (char *)malloc(10);
	if (p->name == NULL)
	{
		free(p);
		return -1;
	}
	strcpy(p->name, "tom");

	printf("name : %s\n", p->name);
	
	free(p->name);
	free(p);

	return 0;
}
