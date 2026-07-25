#include <stdio.h>
#include <stdarg.h>
#include <string.h>
#include <stdlib.h>

//定义学生结构体
struct cls_t{
	/*char name[64];*/
	char *name;
	int age;
	float sum;
	//......
};

int main(void)
{
	//定义学生结构体变量 定义并初始化
	struct cls_t *p = NULL;

	p = (struct cls_t *)malloc(sizeof(struct cls_t));
	if (NULL == p)
	{
		return -1;
	}

	strcpy(p->name, "tom");
	/*p->name = "tom";*/

	p->name[0] = 'T';

	printf("p->name[0]  : %c\n", p->name[0]);
	p->age = 100;
	p->sum = 66.66;

	printf("=========================\n");
	printf("name : %s\n", p->name);
	printf("age : %d\n", p->age);
	printf("sum : %.2f\n", p->sum);
	

	return 0;
}
