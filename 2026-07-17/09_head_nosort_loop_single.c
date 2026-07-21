#include <stdio.h>
#include <stdarg.h>
#include <string.h>
#include <stdlib.h>
#include <share.h>

//定义链表节点信息
struct list_t{
	int data;      //数据域
	struct list_t *next;//指针域
};

//有头 无序 循环 单项
int main(int argc, char *argv[])
{
	//定义头节点
	struct list_t head = {0, &head};
	int num;
	struct list_t *new = NULL;
	struct list_t *tail = NULL;


	//num => new => head
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

		//head
		for (tail = &head; tail->next != &head; tail = tail->next)
		{
			;
		}

		new->next = &head;
		tail->next = new;

	}

	//遍历
	for (tail = head.next; tail != &head; tail = tail->next)
	{
		printf("%d ", tail->data);
	}
	putchar(10);

	//释放
	for (tail = head.next; tail != &head; tail = new)
	{
		new = tail->next;
		free(tail);
	}
	return 0;
}
