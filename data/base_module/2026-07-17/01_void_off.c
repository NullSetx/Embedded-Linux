#include <stdio.h>
#include <stdarg.h>
#include <string.h>
#include <stdlib.h>
#include <share.h>

struct cls_t{
	char name[64];
	int id;
};
int main(int argc, char *argv[])
{
	void *v = NULL;
	struct cls_t *cls = NULL;
	void *data = NULL;

	printf("v : %p v + 1 : %p\n", v, v + 1);
	printf("cls : %p cls + 1 : %p\n", cls, cls + 1);
	printf("data : %p data + 1 : %p\n", data, data + 1);
	printf("data : %p data + 1 : %p\n", data, ((struct cls_t *)data) + 1);
	printf("data : %p data + 1 : %p\n", data, data + 1 * sizeof(struct cls_t));
	return 0;
}
