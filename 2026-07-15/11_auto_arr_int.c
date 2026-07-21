#include <stdio.h>
#include <stdarg.h>
#include <string.h>
#include <stdlib.h>

int main(void)
{
	int i;
	int num;		//临时接受用户输入
	int count = 0;//统计数据个数
	int *new = NULL;//用于保存最新数据空间
	int *prev = NULL;//用于保存原来的数据

	//循环接受用户输入
	while (1)
	{
		printf("input number : ");
		scanf("%d", &num);
		
		//退出条件
		if (num == -1)
		{
			break;
		}

		//新申请的内存空间，用于保存原来的数据和用户输入最新的一个数据
		new = (int *)malloc(sizeof(int) * (count + 1));
		/*new = (int *)realloc(new, sizeof(int) * (count + 1));*/
		if (new == NULL)
		{
			return -1;
		}

		//原来的数据复制到最先的空间地址上
		memcpy(new, prev, sizeof(int) * count);
		//释放原来数据空间	
		free(prev);

		//接受用户数据保存到空间的结尾
		*(new + count) = num;

		//保存最新的数据
		prev = new;

		count++;
	}

	printf("=================\n");
	//遍历
	for (i = 0; i < count; i++)
	{
		printf("%d ", new[i]);
	}
	putchar(10);


	//释放内存空间 销毁
	free(new);
	return 0;
}
