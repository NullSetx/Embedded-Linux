#include <stdio.h>
#include <stdarg.h>
#include <string.h>
#include <stdlib.h>
#include <share.h>

//定义栈大小
#define MAX 10

int is_full(int top)
{
	if (top == MAX)
		return 1;
	return 0;	
}

int is_empty(int top)
{
	if (top == 0)
		return 1;
	return 0;	
}
//入栈
int push(int *stack, int num, int *top)
{

	if (is_full(*top))
		return -1;

	stack[*top] = num;
	(*top)++;

	return 0;
}

//出栈
int pop(int *stack, int *top)
{
	if (is_empty(*top))
		return -1;
	(*top)--;

	return stack[*top];
}

//遍历
void travel(int *stack)
{
	int i;

	for (i = 0; i < MAX; i++)
	{
		printf("%d ", stack[i]);
	}
	putchar(10);
}

int main(int argc, char *argv[])
{
	//定义一个栈空间
	int stack[MAX];
	//栈顶指针或者栈底指针
	int top = 0;
	int num;
	int i, ret;


	for (i = 0; i < MAX + 2; i++)
	{
		num = rand() % 100;
		printf("%d ", num);

		ret = push(stack, num, &top);
		if (ret == -1)
		{
			continue;
		}

	}
	putchar(10);


	travel(stack);
	
	printf("pop : %d\n", pop(stack, &top));
	printf("pop : %d\n", pop(stack, &top));
	printf("pop : %d\n", pop(stack, &top));
	printf("pop : %d\n", pop(stack, &top));

	
	push(stack, 100, &top);
	push(stack, 200, &top);
	push(stack, 300, &top);
	push(stack, 400, &top);
	push(stack, 500, &top);
	push(stack, 600, &top);
	for (i = 0; i < MAX; i++)
	{
		ret = pop(stack, &top);
		if (ret == -1)
		{
			printf("空 ");
		}
		else
		{
			printf("%d ", ret);
		
		}
	}
	putchar(10);
	return 0;
ERR1:
	return -1;
}
