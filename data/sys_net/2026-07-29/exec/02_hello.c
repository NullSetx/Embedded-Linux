#include <stdio.h>


int main(void)
{
	printf("hello : pid = %d ppid = %d\n", getpid(), getppid());

	return 0;
}
