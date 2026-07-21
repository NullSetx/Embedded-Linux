#include <stdio.h>
#include <stdarg.h>
#include <string.h>
#include <stdlib.h>
#include <share.h>

#define MAX 10

//定义哈希节点
struct hash_t{
	int data;
	struct hash_t *next;
};

//哈希算法
int hash(int num)
{
	return num % MAX;
}

int main(int argc, char *argv[])
{
	int i;
	int num;
	//有头 单项 不循环 哈希
	struct hash_t head[MAX] = {};
	struct hash_t *new = NULL;
	struct hash_t *tail = NULL;
	int index;
	int key;


	srand(time(NULL));

	//创建哈希表
	for (i = 0 ; i < MAX; i++)
	{
		num = rand() % 100;
		printf("%d ", num);
		
		new = (struct hash_t *)malloc(sizeof(struct hash_t));
		ERRP(NULL == new, malloc, goto ERR1);
		
		new->data = num;
		new->next = NULL;

		index = hash(num);

		for (tail = &head[index]; tail->next != NULL; tail = tail->next)
			;
		tail->next = new;	

	}
	putchar(10);

	//遍历哈希
	for (i = 0; i < MAX; i++)
	{
		printf("%d : ", i);
		for (tail = head[i].next; tail != NULL; tail = tail->next)
		{
			printf("%d ", tail->data);
		}
		putchar(10);
	}
	putchar(10);
	
	//哈希查找
	printf("input find key :  ");
	scanf("%d", &key);
	index = hash(key);

	for (tail = head[index].next; tail != NULL; tail = tail->next)
	{
		if (tail->data == key)
		{
			printf("find : %d\n", tail->data);
		}
	}


	//哈希销毁
	for (i = 0; i < MAX; i++)
	{
		for (tail = head[i].next; tail != NULL; tail = new)
		{
			new = tail->next;
			free(tail);
			tail = NULL;
		}
	}
	
	return 0;
ERR1:
	return -1;
}


