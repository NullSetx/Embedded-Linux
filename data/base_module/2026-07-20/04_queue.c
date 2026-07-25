#include <stdio.h>
#include <stdarg.h>
#include <string.h>
#include <stdlib.h>
#include <share.h>

//定义队列的大小
#define MAX 10

int is_full(int front, int end)
{
	return (end + 1) % MAX == front ? 1: 0;
}
int is_empty(int front, int end)
{
	return end == front ? 1 : 0;
}

void qe(int *queue, int num, int front, int *end)
{
	//1 判断是否是满队
	if (is_full(front, *end))
		return ;

	//2 入队
	queue[*end] = num;

	//3 队尾偏移
	(*end)++;

	//4 循环队列
	if (*end == MAX)
		*end = 0;
}

int de(int *queue, int *front, int end)
{
	int save;

	//1 判断是否是空队
	if (is_empty(*front, end))
		return -1;
	
	//2 出队
	save =  queue[*front];

	//3 队头偏移
	(*front)++;

	//4 循环队列
	if (*front == MAX)
		*front = 0;

	return save;	
}

int len(int front, int end)
{
	if (end >= front)
		return end - front;
	else
		return MAX - (front - end);
}

void travel(int *queue, int front, int end)
{
	int i, j;
	//有多少个数据就打印多少个， 从队头打印到队尾
	for (i = 0, j = front; i < len(front, end); i++, j++)
	{
		if (j == MAX)
			j = 0;
		printf("%d ", queue[i]);
	}
	putchar(10);
}

int main(int argc, char *argv[])
{
	//定义对取
	int queue[MAX] ;
	int front = 0;//队头
	int end = 0;//队尾
	int num;
	int i;

	for(i = 0 ;i < MAX; i++)
	{
		num = rand() % 100;
		printf("%d ", num);
		qe(queue, num, front, &end);
	}
	putchar(10);
	printf("len : %d\n", len(front, end));
	printf("===================\n");
	travel(queue, front, end);
	printf("===================\n");

	de(queue, &front, end);
	de(queue, &front, end);
	printf("len : %d\n", len(front, end));
	printf("===================\n");
	travel(queue, front, end);
	printf("===================\n");

	qe(queue, 100, front, &end);
	qe(queue, 200, front, &end);
	qe(queue, 300, front, &end);
	printf("len : %d\n", len(front, end));
	de(queue, &front, end);
	de(queue, &front, end);


	for (i = 0 ;i < MAX; i++)
	{
		printf("%d ", de(queue, &front, end));
	}
	printf("\n");
	printf("len : %d\n", len(front, end));
	printf("===================\n");
	travel(queue, front, end);
	printf("===================\n");

	return 0;
}
