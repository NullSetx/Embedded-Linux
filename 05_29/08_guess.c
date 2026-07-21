#include <stdio.h>
#include <stdarg.h>
#include <string.h>

int main(void)
{
	int num;
	int key;

	srand(time(NULL));

	key = rand() % 100;
	while (1)
	{
		printf("input number : ");
		scanf("%d", &num);

		if (num > key)
		{
			printf("little!\n");
		}
		else if (num < key)
		{
			printf("big!\n");
		}
		else
		{
			printf("恭喜你，猜中了!\n");
			break;
		}
	}
	return 0;
}
