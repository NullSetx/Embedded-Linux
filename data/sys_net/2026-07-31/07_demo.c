#include <stdio.h>
#include <stdarg.h>
#include <string.h>
#include <stdlib.h>
#include <share.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>
#include <pwd.h>
#include <grp.h>
#include <shadow.h>
#include <time.h>
#include <dirent.h>
#include <sys/wait.h>
#include <sys/time.h>
#include <sys/resource.h>
#include <signal.h>
#include <sys/ipc.h>
#include <sys/msg.h>
#include <sys/shm.h>
#include <sys/sem.h>
#include <pthread.h>

struct cls_t{
	int a;
};

void test(struct cls_t *a)
{

}

int main(int argc, char *argv[])
{
	struct cls_t a = {123};

	printf("a.a : %d\n", a.a);

	printf("a : %d\n", a);
	test((struct cls_t *)a);
	return 0;
}
