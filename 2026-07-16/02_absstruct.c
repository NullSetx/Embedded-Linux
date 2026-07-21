#include <stdio.h>
#include <stdarg.h>
#include <string.h>
#include <stdlib.h>
#include <share.h>

#define MAX 10

//定义一个函数指针的类型
typedef void (darr_op_t)(const void *);

//抽象数据类型
typedef struct darr_t{
	void *data;//表示数据
	int size;//数据类型
	int num;//数据个数
}DARR;


struct cls_t{
	char name[64];
	int id;
	int age;
	char sex;
	float lin;
	float c;
	float sum;
};

//初始化handle
DARR *darr_creat(int size)
{
	DARR *handle = NULL;

	handle = (DARR *)malloc(sizeof(DARR));
	ERRP(NULL == handle, malloc handle, goto ERR1);

	handle->data = NULL;
	handle->size = size;
	handle->num = 0;

	return handle;
ERR1:
	return NULL;
}

//            数据长度     原来数据    新添加数据  数据大小
void insert(DARR *handle, void *data)
{
	void *new = NULL;

	#if 1
	//新申请的内存空间，用于保存原来的数据和用户输入最新的一个数据
	new = (void *)malloc(handle->size * (handle->num + 1));
	/*new = (void *)realloc(new, sizeof(void) * (count + 1));*/
	if (new == NULL)
	{
		return ;
	}

	//原来的数据复制到最先的空间地址上
	memcpy(new, handle->data, handle->size * handle->num);
	//释放原来数据空间	
	free(handle->data);

	//接受用户数据保存到空间的结尾
	/**(new + *count) = *cls;*/
	memcpy(new + handle->num * handle->size, data, handle->size);
	
	handle->data = new;

	handle->num++;
	#endif
	
}
//遍历函数
void darr_travel(DARR *handle, darr_op_t *op)
{
	int i;
	for (i = 0; i < handle->num; i++)
	{
		//handle->data
		op(handle->data + i * handle->size);
	}
}

//销毁
void darr_destroy(DARR **handle)
{
	free((*handle)->data);
	(*handle)->data = NULL;
	free(*handle);
	*handle = NULL;
}

void ls(const void *data)
{
	struct cls_t *cls = (struct cls_t *)data;
	printf("name : %s id : %d age : %d sex : %c lin : %.2f c : %.2f sun : %.2f\n", cls->name, cls->id, cls->age, cls->sex, cls->lin, cls->c, cls->sum);

}

void ls_int(const void *data)
{
	printf("%d ", *(int *)data);
}

int main(void)
{
	int i;
	int count = 0;//统计数据个数
	struct cls_t cls;		//临时接受用户输入

	DARR *handle = NULL;

	/*handle = darr_creat(sizeof(struct cls_t));*/
	handle = darr_creat(sizeof(int));
	ERRP(NULL == handle, darr_creat, goto ERR1);

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
		
		count = rand() % 100;

		insert(handle, &count);

		/*new = insert(&count, new, &cls, sizeof(struct cls_t));*/
	}

	printf("=================\n");

	//遍历 handle->data
	/*darr_travel(handle, ls);*/
	darr_travel(handle, ls_int);


	//释放内存空间 销毁
	/*free(new);*/
	darr_destroy(&handle);
	return 0;
ERR1:
	return -1;
}
