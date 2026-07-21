#include <stdio.h>
#include <stdarg.h>
#include <string.h>
#include <stdlib.h>
#include <share.h>

//定义单项链表的节点信息
struct list_t{
	int data;			//数据域 保存数据
	struct list_t *next;//指针域 指向下一个节点的地址
};

//有头 无序 不循环 单项链表
int main(int argc, char *argv[])
{
	//定义头节点
	struct list_t head = {0, NULL};
	int num;
	struct list_t *new = NULL;
	struct list_t *tail = NULL;

	while (1)
	{
		//接受用户输入，并保存到临时num中
		printf("input number : ");
		scanf("%d", &num);

		//退出条件
		if (num == -1)
		{
			break;
		}

		//接受临时数据要保存到链表的节点中
		new = (struct list_t *)malloc(sizeof(struct list_t));
		ERRP(new == NULL, malloc, goto ERR1);

		//保存数据到独立节点中
		new->data = num;
		new->next = NULL;
		
		//查找最后一个节点
		for (tail = &head; tail->next != NULL; tail = tail->next)
		{
			if (new->data > tail->next->data)
			{
				break;
			}
		}	
		//把最新的节点连接到最后一个节点后面	
		new->next = tail->next;
		tail->next = new;

	}

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
ERR1:
	return -1;
}
