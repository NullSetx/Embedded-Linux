#ifndef __KEN_STACK_H__
#define __KEN_STACK_H__

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <share.h>

typedef void (stack_op_t)(const void *);


typedef struct stack_t{
	void *stack;
	int size;//数据类型
	int max;//栈大小
	int top;//栈顶指针
}STACK;


STACK *stack_creat(int size, int max);
void stack_destroy(STACK **handle);
int stack_is_full(STACK *handle);
int stack_is_empty(STACK *handle);
void stack_push(STACK *handle, void *data);
void *stack_pop(STACK *handle);
void stack_clean(STACK *handle);
int stack_num(STACK *handle);
void stack_store(STACK *handle, const char *path);
STACK *stack_load(const char *path);
void stack_travel(STACK *handle, stack_op_t *op);


#endif //STACK_H

