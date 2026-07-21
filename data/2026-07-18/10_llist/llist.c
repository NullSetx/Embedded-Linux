#include "llist.h"


//初始化
LLIST *llist_creat(int size)
{
	LLIST *handle = NULL;

	handle = (LLIST *)malloc(sizeof(LLIST));
	ERRP(handle == NULL, malloc, goto ERR1);

	handle->size = size;//数据类型
	handle->num = 0;	//数据个数

	handle->head.data = NULL;// 存储数据
	//循环双向链表
	handle->head.next = &handle->head;
	handle->head.prev = &handle->head;

	return handle;
ERR1:
	return NULL;
}


//=========================insert==============================
int llist_insert_end(LLIST *handle, void *data)
{
	struct node_t *new = NULL;

	ERRP(data == NULL, data arg, goto ERR1);

	//节点申请空间
	new = (struct node_t *)malloc(sizeof(struct node_t));
	ERRP(new == NULL, malloc, goto ERR1);
	//节点中数据申请空间
	new->data = (void *)malloc(handle->size);
	ERRP(NULL == new->data, malloc data, goto ERR2);

	//表示保存数据到节点中
	memcpy(new->data, data, handle->size);

	//节点添加到链表中
	//尾插
	//先写外来的 再谁长写谁
	new->next = &handle->head;
	new->prev = handle->head.prev;
	handle->head.prev->next = new;
	handle->head.prev = new;

	handle->num++;

	return 0;
ERR2:
	free(new);
	new = NULL;
ERR1:
	return -1;
}

int llist_insert_front(LLIST *handle, void *data)
{
	struct node_t *new = NULL;

	ERRP(data == NULL, data arg, goto ERR1);

	//节点申请空间
	new = (struct node_t *)malloc(sizeof(struct node_t));
	ERRP(new == NULL, malloc, goto ERR1);
	//节点中数据申请空间
	new->data = (void *)malloc(handle->size);
	ERRP(NULL == new->data, malloc data, goto ERR2);

	//表示保存数据到节点中
	memcpy(new->data, data, handle->size);

	//节点添加到链表中
	//尾插
	//先写外来的 再谁长写谁
	new->next = handle->head.next;
	new->prev = &handle->head;
	handle->head.next->prev = new;
	handle->head.next = new;

	handle->num++;

	return 0;
ERR2:
	free(new);
	new = NULL;
ERR1:
	return -1;
}

int llist_insert_index(LLIST *handle, void *data, int index)
{
	struct node_t *new = NULL;
	struct node_t *tail = &handle->head;

	ERRP(data == NULL, data arg, goto ERR1);
	ERRP(index < 0 || index > handle->num , index arg, goto ERR1);


	//节点申请空间
	new = (struct node_t *)malloc(sizeof(struct node_t));
	ERRP(new == NULL, malloc, goto ERR1);
	//节点中数据申请空间
	new->data = (void *)malloc(handle->size);
	ERRP(NULL == new->data, malloc data, goto ERR2);

	//表示保存数据到节点中
	memcpy(new->data, data, handle->size);

	while (index--)
	{
		tail = tail->next;
	}

	//节点添加到链表中
	//尾插
	//先写外来的 再谁长写谁
	// tail new tail->next
	new->next = tail->next;
	new->prev = tail;
	tail->next->prev = new;
	tail->next = new;

	handle->num++;

	return 0;
ERR2:
	free(new);
	new = NULL;
ERR1:
	return -1;
}

//=============del==============================
void llist_del_front(LLIST *handle, void *key, llist_cmp_t *cmp)
{
	struct node_t *tail = NULL;

	for (tail = handle->head.next; tail != &handle->head; tail = tail->next)
	{
		if (cmp(tail->data, key) == 0)
		{
			// tail->prev    tail tail->next
			tail->prev->next = tail->next;
			tail->next->prev = tail->prev;
			free(tail->data);
			free(tail);
			handle->num--;
			return ;
		}
	}
	return ;
}


void llist_del_end(LLIST *handle, void *key, llist_cmp_t *cmp)
{
	struct node_t *tail = NULL;

	for (tail = handle->head.prev; tail != &handle->head; tail = tail->prev)
	{
		if (cmp(tail->data, key) == 0)
		{
			// tail->prev    tail tail->next
			tail->prev->next = tail->next;
			tail->next->prev = tail->prev;
			free(tail->data);
			free(tail);
			handle->num--;
			return ;
		}
	}
	return ;
}

void llist_del_index(LLIST *handle, int index)
{
	struct node_t *tail = handle->head.next;

	if (index < 0)
		index = 0;
	if (index >= handle->num)
		index = handle->num - 1;

	while (index--)
	{
		tail = tail->next;
	}

	// tail->prev    tail tail->next
	tail->prev->next = tail->next;
	tail->next->prev = tail->prev;
	free(tail->data);
	free(tail);
	handle->num--;
	return ;
}

void llist_del_all(LLIST *handle, void *key, llist_cmp_t *cmp)
{
	struct node_t *tail = NULL;

	for (tail = handle->head.next; tail != &handle->head; tail = tail->next)
	{
		if (cmp(tail->data, key) == 0)
		{
			// tail->prev    tail tail->next
			tail->prev->next = tail->next;
			tail->next->prev = tail->prev;
			free(tail->data);
			free(tail);
			handle->num--;
		}
	}
	return ;
}


int llist_num(LLIST *handle)
{
	return handle->num;
}

//=================find=======================
void *llist_find_front(LLIST *handle, void *key, llist_cmp_t *cmp)
{
	struct node_t *tail = NULL;

	for (tail = handle->head.next; tail != &handle->head; tail = tail->next)
	{
		if (cmp(tail->data, key) == 0)
		{
			return tail->data;
		}
	}
	return NULL;

}

LLIST *llist_find_all(LLIST *handle, void *key, llist_cmp_t *cmp)
{
	struct node_t *tail = NULL;
	LLIST *ind = NULL;

	ind = llist_creat(handle->size);
	ERRP(ind == NULL, llist_creat, goto ERR1);


	for (tail = handle->head.next; tail != &handle->head; tail = tail->next)
	{
		if (cmp(tail->data, key) == 0)
		{
			llist_insert_front(ind, tail->data);
		}
	}
	return ind;
ERR1:
	return NULL;
}
void *llist_find_end(LLIST *handle, void *key, llist_cmp_t *cmp)
{
	struct node_t *tail = NULL;

	for (tail = handle->head.prev; tail != &handle->head; tail = tail->prev)
	{
		if (cmp(tail->data, key) == 0)
		{
			return tail->data;
		}
	}
	return NULL;

}

void *llist_find_index(LLIST *handle, int index)
{
	struct node_t *tail = handle->head.next;

	if (index < 0)
		index = 0;
	if (index >= handle->num)
		index = handle->num - 1;
	
	while (index--)
	{
		tail = tail->next;
	}
	
	return tail->data;
}

//=============mod=========================
void llist_mod_front(LLIST *handle, void *key1, llist_cmp_t *cmp, void *key2, llist_mod_t *mod)
{
	struct node_t *tail = NULL;

	for (tail = handle->head.next; tail != &handle->head; tail = tail->next)
	{
		if (cmp(tail->data, key1) == 0)
		{
			mod(tail->data, key2);
			return ;
		}
	}

	return ;
}

void llist_mod_end(LLIST *handle, void *key1, llist_cmp_t *cmp, void *key2, llist_mod_t *mod)
{
	struct node_t *tail = NULL;

	for (tail = handle->head.prev; tail != &handle->head; tail = tail->prev)
	{
		if (cmp(tail->data, key1) == 0)
		{
			mod(tail->data, key2);
			return ;
		}
	}

	return ;
}

void llist_mod_all(LLIST *handle, void *key1, llist_cmp_t *cmp, void *key2, llist_mod_t *mod)
{
	struct node_t *tail = NULL;

	for (tail = handle->head.next; tail != &handle->head; tail = tail->next)
	{
		if (cmp(tail->data, key1) == 0)
		{
			mod(tail->data, key2);
		}
	}

	return ;
}


void llist_mod_index(LLIST *handle, int index, void *key2, llist_mod_t *mod)
{
	struct node_t *tail = handle->head.next;

	if (index < 0)
		index = 0;
	if (index >= handle->num)
		index = handle->num - 1;
	
	while (index--)
	{
		tail = tail->next;
	}
	
	mod(tail->data, key2);
}


//=============sort===================
void llist_sort(LLIST *handle, llist_sort_t *sort, SORT flag )
{
	struct node_t *tail1 = NULL, *tail2 = NULL;
	void *tmp = NULL;


	for (tail1 = handle->head.next; tail1 != &handle->head; tail1 = tail1->next)
	{
		for (tail2 = tail1->next; tail2 != &handle->head; tail2 = tail2->next)
		{
			if (flag == ASCENDING)
			{
				if (sort(tail1->data, tail2->data) > 0)
				{
					tmp = tail1->data;
					tail1->data = tail2->data;
					tail2->data = tmp;
				}
			}
			else
			{
				if (sort(tail1->data, tail2->data) < 0)
				{
					tmp = tail1->data;
					tail1->data = tail2->data;
					tail2->data = tmp;
				}
			
			}
		}
	}
}


//=============store and load ================
void  llist_store(LLIST *handle, const char *path)
{
	FILE *fp = NULL;
	int ret;
	struct node_t *tail = NULL;


	//打开文件
	ERRP(NULL == (fp = fopen(path, "w")), fopen, goto ERR1);

	//存储数据类型
	ERRP(fwrite(&handle->size, sizeof(handle->size), 1, fp) != 1, fwrite size, goto ERR2);

	//存储数据大小
	ERRP(fwrite(&handle->num, sizeof(handle->num), 1, fp) != 1, fwrite num, goto ERR2);
	//
	//存储数据
	for (tail = handle->head.next; tail != &handle->head; tail = tail->next)
	{
		fwrite(tail->data, handle->size, 1, fp);
	}	

	//关闭文件
	fclose(fp);
	return ;
ERR2:
	fclose(fp);
ERR1:
	return ;
}

LLIST *llist_load(const char *path)
{
	FILE *fp = NULL;
	LLIST *handle = NULL;
	int size, num;
	int i;
	void *tmp = NULL;

	fp = fopen(path, "r");
	ERRP(fp == NULL, fopen, goto ERR1);

	//读取数据类型
	ERRP(1 != fread(&size, sizeof(size), 1, fp), fread size, goto ERR2);
	//读取数据大小
	ERRP(1 != fread(&num, sizeof(num), 1, fp), fread num, goto ERR2);
	/*printf("size : %d num : %d\n", size, num);*/

	//handle初始化
	handle = llist_creat(size);
	ERRP(handle == NULL, llist_creat, goto ERR2);

	//读数据
	tmp = (void *)malloc(size);
	ERRP(NULL == tmp, malloc, goto ERR3);

	for (i = 0; i < num; i++)
	{
		ERRP(fread(tmp, size, 1, fp) != 1, fread data, goto ERR4);
		llist_insert_front(handle, tmp);

	}


	free(tmp);
	tmp = NULL;
	fclose(fp);

	return handle;
ERR4:
	free(tmp);
ERR3:
	llist_destroy(&handle);
ERR2:
	fclose(fp);
ERR1:
	return NULL;
}


//===============travel==========================
void llist_travel_next(LLIST *handle, llist_op_t *op)
{
	struct node_t *tail = NULL;

	for (tail = handle->head.next; tail != &handle->head; tail = tail->next)
	{
		op(tail->data);
	}
}


void llist_travel_prev(LLIST *handle, llist_op_t *op)
{
	
	struct node_t *tail = NULL;

	for (tail = handle->head.prev; tail != &handle->head; tail = tail->prev)
	{
		op(tail->data);
	}
}

void llist_destroy(LLIST **handle)
{
	struct node_t *tail = NULL;
	struct node_t *save = NULL;

	for (tail = (*handle)->head.next; tail != &(*handle)->head; tail = save)
	{
		save = tail->next;
		free(tail->data);
		tail->data = NULL;
		free(tail);
		tail = NULL;
	}

	free(*handle);
	*handle = NULL;
}








