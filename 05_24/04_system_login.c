#include <stdio.h>
#include <stdarg.h>
#include <string.h>

int main(void)
{
	int sel;

	printf("===> system menu <===\n");
	printf("=> 1 windows       <=\n");
	printf("=> 2 red hat       <=\n");
	printf("=> 3 Ubuntu        <=\n");
	printf("=> 4 CentOS        <=\n");
	printf("=> 5 Debian        <=\n");
	printf("input system : ");
	scanf("%d", &sel);

	switch (sel)
	{
		default:
			printf("input option error\n");
			break;
		case 3:
		case 6:
		case 7:
		case 8:
			printf("welcome to Ubuntu ...\n");
			break;
		case 1:
			printf("welcome to windows ...\n");
			break;
		case 2:
			printf("welcome to red hat ...\n");
			break;
		case 4:
			printf("welcome to CentOS ...\n");
			break;
		case 5:
			printf("welcome to Debian ...\n");
			break;
	}
	return 0;
}
