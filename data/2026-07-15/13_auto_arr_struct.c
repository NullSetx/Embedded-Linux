#include <stdio.h>
#include <stdarg.h>
#include <string.h>
#include <stdlib.h>

#define MAX 10

struct cls_t{
	char name[64];
	int id;
	int age;
	char sex;
	float lin;
	float c;
	float sum;
};


insert()
{

}

int main(void)
{
	int i;
	int count = 0;//统计数据个数
	struct cls_t cls;		//临时接受用户输入
	struct cls_t *new = NULL;//用于保存最新数据空间
	struct cls_t *prev = NULL;//用于保存原来的数据

	//循环接受用户输入
	for (i = 0; i < MAX; i++)
	{
		
		snprintf(cls.name, sizeof(cls.name), "cls_%c%c", rand() % 26 + 'A', rand() % 26 + 'a');
		cls.id = 1122000 + rand() % 1000;
		cls.age = rand() % 3 + 17;
		cls.sex = "MF"[rand() % 2];
		cls.lin = 30.0 * (rand() / (RAND_MAX + 1.0)) + 70;
		cls.c = 20.0 * (rand() / (RAND_MAX + 1.0)) + 80;
		cls.sum = cls.lin + cls.c;

		insert();
		#if 0
		//新申请的内存空间，用于保存原来的数据和用户输入最新的一个数据
		new = (struct cls_t *)malloc(sizeof(struct cls_t) * (count + 1));
		/*new = (struct cls_t *)realloc(new, sizeof(struct cls_t) * (count + 1));*/
		if (new == NULL)
		{
			return -1;
		}

		//原来的数据复制到最先的空间地址上
		memcpy(new, prev, sizeof(struct cls_t) * count);
		//释放原来数据空间	
		free(prev);

		//接受用户数据保存到空间的结尾
		*(new + count) = cls;

		//保存最新的数据
		prev = new;

		count++;
		#endif
	}

	printf("=================\n");
	//遍历
	for (i = 0; i < count; i++)
	{
		printf("name : %s id : %d age : %d sex : %c lin : %.2f c : %.2f sun : %.2f\n", new[i].name, new[i].id, new[i].age, new[i].sex, new[i].lin, new[i].c, new[i].sum);
	}
	putchar(10);


	//释放内存空间 销毁
	free(new);
	return 0;
}
