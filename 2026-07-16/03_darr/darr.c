#include "darr.h"

//
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
//====================insert===================================
//            数据长度     原来数据    新添加数据  数据大小
void darr_insert_end(DARR *handle, const void *data)
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


//表示前插
void darr_insert_front(DARR *handle, const void *data)
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
	memcpy(new + handle->size, handle->data, handle->size * handle->num);
	//释放原来数据空间	
	free(handle->data);

	//接受用户数据保存到空间的结尾
	/**(new + *count) = *cls;*/
	memcpy(new, data, handle->size);
	
	handle->data = new;

	handle->num++;
	#endif
	
}

//指定位置插入
void darr_insert_index(DARR *handle, const void *data, int index)
{
	void *new = NULL;

	ERRP(handle == NULL, first_handle_arg, goto ERR1);
	ERRP(data == NULL, second_data_arg, goto ERR1);
	ERRP(index < 0 || index > handle->num, three_index_arg, goto ERR1);



	#if 1
	//新申请的内存空间，用于保存原来的数据和用户输入最新的一个数据
	new = (void *)malloc(handle->size * (handle->num + 1));
	ERRP(new == NULL, malloc, goto ERR1);


	//1>先拷贝handle->data的前半部分到new中
	memcpy(new, handle->data, handle->size * index);
	//2>拷贝新来的数据data到new
	memcpy(new + handle->size * index, data, handle->size);
	//3>拷贝handle->data的后半部分到new
	memcpy(new + handle->size * (index + 1), handle->data + handle->size * index, handle->size * (handle->num - index));

	//释放原来数据空间	
	free(handle->data);
	
	handle->data = new;

	handle->num++;
	#endif
	
	return ;
ERR1:
	return ;
}


//=================del==============================
//
void darr_del_front(DARR *handle, const void *key, darr_cmp_t *cmp)
{
	int i;
	void *new = NULL;


	for (i = 0; i < handle->num; i++)
	{
		if (cmp(handle->data + i * handle->size, key) == 0)
		{
			new = (void *)malloc(handle->size * (handle->num - 1));
			ERRP(new == NULL,  malloc, goto ERR1);

			memcpy(new, handle->data, handle->size * i);
			memcpy(new + handle->size * i, handle->data + handle->size * (i + 1), handle->size * (handle->num - i - 1));
			free(handle->data);
			handle->data = new;
			handle->num--;
			return ;
		}
	}

	return ;
ERR1:
	return ;
}
//

void darr_del_end(DARR *handle, const void *key, darr_cmp_t *cmp)
{
	int i;
	void *new = NULL;


	for (i = handle->num - 1; i >= 0; i--)
	{
		if (cmp(handle->data + i * handle->size, key) == 0)
		{
			new = (void *)malloc(handle->size * (handle->num - 1));
			ERRP(new == NULL,  malloc, goto ERR1);

			memcpy(new, handle->data, handle->size * i);
			memcpy(new + handle->size * i, handle->data + handle->size * (i + 1), handle->size * (handle->num - i - 1));
			free(handle->data);
			handle->data = new;
			handle->num--;
			return ;
		}
	}

	return ;
ERR1:
	return ;
}
//
void darr_del_index(DARR *handle, int index)
{
	int i;
	void *new = NULL;

	ERRP(index < 0 || index >= handle->num, index, goto ERR1);

	new = (void *)malloc(handle->size * (handle->num - 1));
	ERRP(new == NULL,  malloc, goto ERR1);

	memcpy(new, handle->data, handle->size * index);
	memcpy(new + handle->size * index, handle->data + handle->size * (index + 1), handle->size * (handle->num - index - 1));
	free(handle->data);
	handle->data = new;
	handle->num--;

	return ;
ERR1:
	return ;
}
//
//
void darr_del_all(DARR *handle, const void *key, darr_cmp_t *cmp)
{
	int i;
	void *new = NULL;


	for (i = 0; i < handle->num; i++)
	{
		if (cmp(handle->data + i * handle->size, key) == 0)
		{
			new = (void *)malloc(handle->size * (handle->num - 1));
			ERRP(new == NULL,  malloc, goto ERR1);

			memcpy(new, handle->data, handle->size * i);
			memcpy(new + handle->size * i, handle->data + handle->size * (i + 1), handle->size * (handle->num - i - 1));
			free(handle->data);
			handle->data = new;
			handle->num--;
			i--;
		}
	}

	return ;
ERR1:
	return ;
}
//
//===============find=====================
DARR *darr_find_all(DARR *handle, const void *key, darr_cmp_t *cmp)
{
	int i;
	DARR *ind = NULL;

	ind = darr_creat(handle->size);
	ERRP(NULL == ind, darr_creat, goto ERR1);


	for (i = 0; i < handle->num; i++)
	{
		if (cmp(handle->data + i * handle->size, key) == 0)
		{
			darr_insert_front(ind, handle->data + i * handle->size);
		}
	}

	return ind;
ERR1:
	return NULL;
}

//                    形参                              cmp_name cmp_age
void *darr_find_front(DARR *handle, const void *key, darr_cmp_t *cmp)
{
	int i;
	for (i = 0; i < handle->num; i++)
	{
		if (cmp(handle->data + i * handle->size, key) == 0)
		{
			return handle->data + i * handle->size;
		}
	}
	return NULL;
}
void *darr_find_end(DARR *handle, const void *key, darr_cmp_t *cmp)
{
	int i;
	for (i = handle->num - 1; i >= 0; i--)
	{
		if (cmp(handle->data + i * handle->size, key) == 0)
		{
			return handle->data + i * handle->size;
		}
	}
	return NULL;

}
void *darr_find_index(DARR *handle, int index)
{
	if (index < 0)
		return handle->data;
	if (index >= handle->num)
		return handle->data + handle->num * handle->size;
	return handle->data + index * handle->size;
}


//==============mod===========================
void darr_mod_front(DARR *handle, const void *old_key, darr_cmp_t *cmp, void *new_key, darr_mod_t *mod)
{
	int i;

	for (i = 0; i < handle->num; i++)
	{
		if (cmp(handle->data + i * handle->size, old_key) == 0)
		{
			mod(handle->data + i * handle->size, new_key);
			return ;
		}
	}

	return ;
}

void darr_mod_end(DARR *handle, const void *old_key, darr_cmp_t *cmp, void *new_key, darr_mod_t *mod)
{
	int i;

	for (i = handle->num - 1; i >= 0; i--)
	{
		if (cmp(handle->data + i * handle->size, old_key) == 0)
		{
			mod(handle->data + i * handle->size, new_key);
			return ;
		}
	}

	return ;
}

void darr_mod_index(DARR *handle, int index, void *new_key, darr_mod_t *mod)
{
	if (index < 0 || index >= handle->num)
		return ;

	mod(handle->data + index * handle->size, new_key);

}
void darr_mod_all(DARR *handle, const void *old_key, darr_cmp_t *cmp, void *new_key, darr_mod_t *mod)
{
	int i;

	for (i = 0; i < handle->num; i++)
	{
		if (cmp(handle->data + i * handle->size, old_key) == 0)
		{
			mod(handle->data + i * handle->size, new_key);
		}
	}

	return ;
}

int darr_num(DARR *handle)
{
	return handle->num;
}

void darr_sort_ascending(DARR *handle, darr_sort_t *sort)
{
	int i,j;
	void *tmp = NULL;

	tmp = (void *)malloc(handle->size);
	ERRP(tmp == NULL, malloc, goto ERR1);

	for (i = 0; i < handle->num; i++)
	{
		for (j = i + 1; j < handle->num; j++)
		{
			if (sort(handle->data + i * handle->size, handle->data + j * handle->size) > 0)
			{
				/*printf("hello!\n");*/
				memmove(tmp, handle->data + i * handle->size, handle->size);
				/*printf("hello!\n");*/
				memmove(handle->data + i * handle->size , handle->data + j * handle->size, handle->size);
				memmove(handle->data + j * handle->size,  tmp, handle->size);

			}
		}
	}
	free(tmp);
	tmp = NULL;
	return ;
ERR1:
	return ;
}
void darr_sort_descending(DARR *handle, darr_sort_t *sort)
{

}
//===============fileIO========================
//
void darr_store(DARR *handle, const char *path)
{
	FILE *fp = NULL;
	int ret;
	//r+ w w+ a a+
	//
	fp = fopen(path, "w");
	ERRP(NULL == fp, fopen, goto ERR1);

	//数据类型
	ret = fwrite(&handle->size, sizeof(handle->size), 1, fp);
	ERRP(ret != 1, fwrite size, goto ERR2);

	//数据个数
	ret = fwrite(&handle->num, sizeof(handle->num), 1, fp);
	ERRP(ret != 1, fwrite num, goto ERR2);
	
	//
	//存储数据
	ret = fwrite(handle->data, handle->size, handle->num, fp);
	ERRP(ret != handle->num, fwrite, goto ERR2);

	fclose(fp);

	return ;
ERR2:
	fclose(fp);
ERR1:
	return ;
}


DARR *darr_load(const char *path)
{
	FILE *fp = NULL;
	DARR *handle = NULL;
	int size, num;
	int ret;


	fp = fopen(path, "r");
	ERRP(fp == NULL, fopen, goto ERR1);

	ret = fread(&size, sizeof(size), 1, fp);
	ERRP(ret != 1, frread size, goto ERR2);

	ret = fread(&num, sizeof(num), 1, fp);
	ERRP(ret != 1, fread num, goto ERR2);

	printf("size : %d num : %d\n", size, num);

	handle = darr_creat(size);
	ERRP(NULL == handle, darr_creat, goto ERR2);

	handle->data = (void *)malloc(size * num);
	ERRP(handle->data == NULL, malloc data, goto ERR3);

	ret = fread(handle->data, size, num, fp);
	ERRP(ret != num, fread data, goto ERR4);

	printf("handle->num : %d\n", handle->num);
	handle->num = num;

	fclose(fp);
	return handle;
ERR4:
	free(handle->data);
	handle->data = NULL;
ERR3:
	darr_destroy(&handle);
ERR2:
	fclose(fp);
ERR1:
	return NULL;
	
}
//



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

