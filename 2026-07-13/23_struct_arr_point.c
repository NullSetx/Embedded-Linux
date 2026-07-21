#include <stdio.h>
#include <stdarg.h>
#include <string.h>
#include <stdlib.h>

typedef void (GAME)(const char *);
typedef void (LOVE)(char *);

void game(const char *name)
{
	printf("%s\n", name);
}

void love(char *name)
{
	printf("%s\n", name);
}

struct cls_t{
	char name[64];
	char *game_name[10];//指针数组
	GAME *play;//函数指针
	char *beautiful_girl[5];
	LOVE *friend;//函数指针
	
};

int main(void)
{
	int i;
	struct cls_t cls = {"tom", {"cs", "斗地主", "五子棋"}, game, {"xiaohua", "ruhua", "donghua"},love};
	
	for (i = 0; i < 3; i++)
		cls.play(cls.game_name[i]);

	for (i = 0; i < 3; i++)
	{
		cls.friend(cls.beautiful_girl[i]);
	}
	return 0;
}
