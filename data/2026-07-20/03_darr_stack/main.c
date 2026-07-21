#include "stack.h"

#define MAX 10

//学生结构体为例
struct cls_t{
	char name[64];
	int id;
	int age;
	char sex;
	float lin;
	float c;
	float sum;
};

//==============cmp==================
int cmp_name(const void *d1, const void *d2)
{
	return strcmp(((struct cls_t *)d1)->name, (char *)d2);
}
int cmp_id(const void *d1, const void *d2)
{
	return (((struct cls_t *)d1)->id - *(int *)d2);
}
int cmp_age(const void *d1, const void *d2)
{
	return (((struct cls_t *)d1)->age - *(int *)d2);
}
int cmp_sex(const void *d1, const void *d2)
{
	return (((struct cls_t *)d1)->sex - *(char *)d2);
}

//==============mod==================
void mod_name(void *d1, const void *d2)
{
	strcpy(((struct cls_t *)d1)->name, (char *)d2);
}
void mod_id(void *d1, const void *d2)
{
	(((struct cls_t *)d1)->id = *(int *)d2);
}
void mod_age(void *d1, const void *d2)
{
	 (((struct cls_t *)d1)->age = *(int *)d2);
}
void mod_sex(void *d1, const void *d2)
{
	 (((struct cls_t *)d1)->sex = *(char *)d2);
}


//==============sort================
int sort_name(const void *d1, const void *d2)
{
	return strcmp(((struct cls_t *)d1)->name, ((struct cls_t *)d2)->name);
}
int sort_id(const void *d1, const void *d2)
{
	return (((struct cls_t *)d1)->id - ((struct cls_t *)d2)->id);
}
int sort_age(const void *d1, const void *d2)
{
	return (((struct cls_t *)d1)->age - ((struct cls_t *)d2)->age);
}
int sort_sex(const void *d1, const void *d2)
{
	return (((struct cls_t *)d1)->sex - ((struct cls_t *)d2)->sex);
}


int sort_sum(const void *d1, const void *d2)
{
	float f;

	f = ((struct cls_t *)d1)->sum - ((struct cls_t *)d2)->sum;
	/*printf("f : %f\n", f);*/
	//0.000534
	if (f > -0.005 && f < 0.005)
		return 0;
	else if (f > 0.00001)
		return 1;
	else
		return -1;
		
}

void ls(const void *data)
{
	struct cls_t *cls = (struct cls_t *)data;
	printf("name : %s id : %d age : %d sex : %c lin : %.2f c : %.2f sun : %.2f\n", cls->name, cls->id, cls->age, cls->sex, cls->lin, cls->c, cls->sum);

}



int main(int argc, char *argv[])
{
	int i;
	struct cls_t cls, *p_cls = NULL;		//临时接受用户输入
	STACK *handle = NULL;
	int ret;
	struct cls_t stu = {"tom", 10086, 20, 'M', 88.99, 99.88, 88.99 + 99.88};

	if (argc == 2)
	{
		handle = stack_load("./stack.db");
		stack_travel(handle, ls);
		return 0;
	}



	handle = stack_creat(sizeof(struct cls_t), MAX);

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
		

		//入栈
		stack_push(handle, &cls);
	}
	printf("==========travel=============\n");
	stack_travel(handle, ls);

	printf("========pop==========\n");
	for (i = 0; i < 5; i++)
	{
		ls(stack_pop(handle));
	}
	
	stack_store(handle, "stack.db");

	//size 88 * 5 + 12 = 440 + 12 = 452
	return 0;
ERR2:
ERR1:
	return -1;
}
