#include <stdio.h>
#include <stdarg.h>
#include <string.h>
#include <stdlib.h>
#include <share.h>

//定义单项链表节点信息
struct list_t{
	int data;		//数据域  接受用户数据
	struct list_t *next; //指针域 指向下一个节点地址
};


//有头 无序  不循环  单项链表
int main(int argc, char *argv[])
{
	int count = 0;
	//定义头节点
	struct list_t head = {0, NULL};
	int num;//临时接受用户输入
	struct list_t *new = NULL;
	struct list_t *tail = NULL;
	struct list_t *save  = NULL, *prev = NULL;

	while (1)
	{
		printf("input number : ");
		scanf("%d", &num);

		if (num == -1)
		{
			break;
		}

		//临时接受的数据保存到节点中
		new = (struct list_t *)malloc(sizeof(struct list_t));
		if (new == NULL)
		{
			return -1;
		}

		new->data = num;
		new->next = NULL;
		

		for (tail = &head; tail->next != NULL; tail = tail->next)
		{
			;
		}

		tail->next = new;
	}

	//遍历
	for (tail = head.next; tail != NULL; tail = tail->next)
	{
		printf("%d ", tail->data);
	}
	putchar(10);
	//=========================
	tail = head.next;
	while (tail != NULL)
	{
		save = tail->next;

		tail->next = prev;
		prev = tail;

		tail = save;
	}
	putchar(10);
	head.next = prev;
		
	//==========================
	//遍历
	for (tail = head.next; tail != NULL; tail = tail->next)
	{
		printf("%d ", tail->data);
	}
	putchar(10);
	//销毁
	for (tail = head.next; tail != NULL; tail = new)
	{
		new = tail->next;
		free(tail);
		tail = NULL;
	}
	return 0;
}
