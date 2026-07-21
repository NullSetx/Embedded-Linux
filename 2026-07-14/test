#include <stdio.h>
#include <stdarg.h>
#include <string.h>
#include <stdlib.h>

struct cls_t{
	char name[64];
	int id;
}cls = {"jim", 10088}, cls3;


typedef struct student_t{
	char name[64];
	int id;
}STU;


int main(void)
{
	struct cls_t cls1 = {"tom", 100086}, cls2;
	STU stu;

    /*
	 *cls2 = cls1;//yes
	 *cls2.name = cls1.name;//no
     */
	
	printf("name : %s id : %d\n", cls.name, cls.id);
	memcpy(&stu, &cls1, sizeof(cls1));

	printf("name : %s id : %d\n", cls2.name, cls2.id);
	printf("name : %s id : %d\n", stu.name, stu.id);
	return 0;
}
