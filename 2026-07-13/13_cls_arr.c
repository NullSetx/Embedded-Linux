#include <stdio.h>
#include <stdarg.h>
#include <string.h>
#include <stdlib.h>

#define MAX 10


//定义学生结构体
struct cls_t{
	char name[64];
	int age;
	float sum;
	//......
};

int main(void)
{
	int i;
	//结构体数组
	struct cls_t cls[MAX] = {{"tom", 18, 88.99}, 
							 {"jim", 19, 99.99}, 
							 {"mary", 17, 66.77}};

	
	for (i = 0; i < 3; i++)
	{
		printf("name : %s age : %d sum : %.2f\n", 
			cls[i].name, (cls + i)->age, cls[i].sum);
	}


	return 0;
}
