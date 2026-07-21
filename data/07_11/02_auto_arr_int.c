#include <stdio.h>
#include <stdarg.h>
#include <string.h>
#include <stdlib.h>

int main(void)
{
	int num;
	int count = 0;//用于计数
	int *new = NULL;
	int *prev = NULL;
	int i;

	while (1)
	{
		printf("input number :  ");
		scanf("%d", &num);

		if (num == -1)
		{
			break;
		}
		new = (int *)malloc(sizeof(int) * (count + 1));
		/*new = (int *)realloc(new, sizeof(int) * (count + 1));*/
		if (new == NULL)
		{
			return -1;
		}
		printf("new : %p\n", new);
		//new = prev;
        /*
		 *for (i = 0; i < count; i++)
		 *{
		 *    new[i] = prev[i];
		 *}
         */
		memcpy(new, prev, sizeof(int) * count);
		free(prev);
		new[count] = num;

		prev = new;//保存原来数据空间地址

		printf("num : %d\n", num);
		count++;
	}

	for (i = 0; i < count; i++)
	{
		printf("%d ", new[i]);
	}
	putchar(10);


	free(new);
	new = NULL;
	return 0;
}
