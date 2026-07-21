#include "stack.h"
STACK *stack_creat(int size, int max)
{
	STACK *handle = NULL;

	handle = (STACK *)malloc(sizeof(STACK));
	ERRP(NULL == handle, malloc, goto ERR1);

	handle->stack = (void *)malloc(max * size);
	ERRP(NULL == handle->stack, malloc stack, goto ERR2);


	handle->size = size;
	handle->max = max;
	handle->top = 0;


	return handle;
ERR2:
	free(handle);
	handle = NULL;
ERR1:
	return NULL;
}
void stack_destroy(STACK **handle)
{
	free((*handle)->stack);
	(*handle)->stack = NULL;
	free(*handle);
	*handle = NULL;
}
int stack_is_full(STACK *handle)
{
	return handle->top == handle->max ? 1: 0;
}
int stack_is_empty(STACK *handle)
{
	return handle->top == 0 ? 1 : 0;
}
void stack_push(STACK *handle, void *data)
{
	//1 判断是否是满栈
	if (stack_is_full(handle))
		return ;

	//2 入栈数据
	memcpy(handle->stack + handle->top * handle->size, data, handle->size);

	//3 栈顶指针偏移
	handle->top++;

	return ;
}
void *stack_pop(STACK *handle)
{
	//1 判断是否是空栈
	if (stack_is_empty(handle))
		return NULL;

	//2 偏移栈顶指针
	handle->top--;

	//3 出栈
	return handle->stack + handle->top * handle->size;
}
void stack_clean(STACK *handle)
{
	handle->top = 0;
}
int stack_num(STACK *handle)
{
	return handle->top;
}
void stack_store(STACK *handle, const char *path)
{
	FILE *fp = NULL;

	fp = fopen(path, "w");
	ERRP(NULL == fp, fopen, goto ERR1);

	//size
	ERRP(fwrite(&handle->size, sizeof(handle->size), 1, fp) != 1, fwrite size, goto ERR2);

	//max
	ERRP(fwrite(&handle->max, sizeof(handle->max), 1, fp) != 1, fwrite max, goto ERR2);
	//
	//top
	ERRP(fwrite(&handle->top, sizeof(handle->top), 1, fp) != 1, fwrite top, goto ERR2);
	//
	//data
	ERRP(fwrite(handle->stack, handle->size, handle->top, fp) != handle->top, fwrite data, goto ERR2);

	fclose(fp);
	return ;
ERR2:
	fclose(fp);
ERR1:
	return ;
}
STACK *stack_load(const char *path)
{
	FILE *fp = NULL;
	STACK *handle = NULL;
	int size, max, top;

	fp = fopen(path, "r");
	ERRP(NULL == fp, fopen, goto ERR1);

	fread(&size, sizeof(size), 1, fp);

	fread(&max, sizeof(max), 1, fp);

	fread(&top, sizeof(top), 1, fp);

	printf("size : %d max : %d top : %d\n", size, max, top);

	handle = stack_creat(size, max);

	fread(handle->stack, size, top, fp);

	handle->top = top;

	return handle;

ERR1:
	return NULL;

}
void stack_travel(STACK *handle, stack_op_t *op)
{
	int i;

	for (i = 0; i < handle->top; i++)
	{
		op(handle->stack + i * handle->size);
	}
}

