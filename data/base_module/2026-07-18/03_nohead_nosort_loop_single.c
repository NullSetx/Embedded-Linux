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


//无头 无序  循环  单项链表
int main(int argc, char *argv[])
{
	int count = 0;
	//定义头节点
	struct list_t *head = NULL;
	int num;//临时接受用户输入
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

		//临时接受的数据保存到节点中
		new = (struct list_t *)malloc(sizeof(struct list_t));
		if (new == NULL)
		{
			return -1;
		}

		new->data = num;
		new->next = NULL;
		
		if (head == NULL)
		{
			new->next = new;  //循环
			head = new;
		}
		else
		{
			for (tail = head; tail->next != head; tail = tail->next)
			{
				;
			}
			new->next = head;
			tail->next = new;
		}
	}

	for (tail = head; tail->next != head; tail = tail->next)
	{
		printf("%d ", tail->data);
	}
	printf("%d\n", tail->data);

	for (tail = head; tail->next != head; tail = new)
	{
		new = tail->next;
		free(tail);
		tail = NULL;
	}
    /*
	 *printf("first : %d\n", head.next->data);
	 *printf("second  : %d\n", head.next->next->data);
	 *printf("three  : %d\n", head.next->next->next->data);
     */
	return 0;
}
