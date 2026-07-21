#include <stdio.h>
#include <stdarg.h>
#include <string.h>
#include <stdlib.h>
#include <share.h>

//定义双向链表节点信息
struct list_t{
	int data;
	struct list_t *next; //指向下一个节点
	struct list_t *prev;//指向上一个节点
};

//有头 无序 循环 双向链表
int main(int argc, char *argv[])
{
	//定义头节点
	struct list_t head = {0, &head, &head};
	int num;
	struct list_t *new = NULL;
	struct list_t *tail = NULL;


	while (1)
	{
		printf("input number : ");
		scanf("%d", &num);

		if (num == -1)
		{
			break;
		}
		
		new = (struct list_t *)malloc(sizeof(struct list_t));
		if (new == NULL)
		{
			return -1;
		}

		new->data = num;
		new->next = NULL;
		new->prev = NULL;

		//先写外来的数据 再谁长写谁
		new->next = &head;//yes
		new->prev = head.prev;//new->prev = head.prev
		head.prev->next = new;//head.next->next = new
		head.prev = new;
	}
	
	printf("next : ");
	for (tail = head.next; tail != &head; tail = tail->next)
	{
		printf("%d ", tail->data);
	}
	putchar(10);
	printf("prev : ");
	for (tail = head.prev; tail != &head; tail = tail->prev)
	{
		printf("%d ", tail->data);
	}
	putchar(10);

	return 0;
}
