#include <stdio.h>
#include <stdarg.h>
#include <string.h>
#include <stdlib.h>

#define MAX 10


//定义学生结构体
struct cls_t{
	char name[64];
	int id;
	int age;
	char sex;
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

	for (i = 0; i < MAX; i++)
	{
		snprintf(cls[i].name, sizeof(cls[i].name), "cls_%c%c", rand() % 26 + 'A', rand() % 26 + 'a');
		cls[i].id = 121323000 + rand() % 1000;
		cls[i].age = rand() % 3 + 17;
		cls[i].sex = "MF"[rand() % 2];
		cls[i].sum = (rand() / (RAND_MAX + 1.0)) * 20 + 80;
	}
	
	for (i = 0; i < MAX; i++)
	{
		printf("name : %s | id : %d | age : %d | sex : %c | sum : %.2f\n", 
			cls[i].name, cls[i].id, (cls + i)->age, cls[i].sex, cls[i].sum);
	}


	return 0;
}
