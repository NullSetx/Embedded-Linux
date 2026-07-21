#include <stdio.h>
#include <stdarg.h>
#include <string.h>
#include <stdlib.h>
#include "vt.h"



#define ROW 15
#define COL 40
#define NUM 10

int flag[] = {1, -1};

struct ball_t{
	int x;
	int y;
	int x_inc;
	int y_inc;
	int color;
	int h;
	int w;
	char ch;
};

void init_ball(struct ball_t *ball)
{
	int i;

	for (i = 0; i < NUM; i++)
	{
		ball[i].h = rand() % 4 + 1;
		ball[i].w = rand() % 8 + 1;
		ball[i].x = (rand() % (ROW - 6)) + 2;
		ball[i].y = (rand() % (COL - 10)) + 2;
		ball[i].x_inc = flag[rand() % 2];
		ball[i].y_inc = flag[rand() % 2];
		ball[i].color = rand() % 7 + 31;
		ball[i].ch = rand() % 26 + 'A';
	}
}


void move(int *x, int *y, int *x_inc, int *y_inc, int *color, int h, int w)
{
	if (*x + h > ROW || *x < 2)
	{
		*x_inc = -*x_inc;
		*color = rand() % 7 + 31;
	}
	if (*y + w > COL || *y < 2)
	{
		*y_inc = -*y_inc;
		*color = rand() % 7 + 31;
	}

	*x += *x_inc;
	*y += *y_inc;

}


int main(void)
{
	int i;
	struct ball_t ball[NUM] = {};

	//初始化弹球
	init_ball(ball);

	#if 1
	printf("hello world!\n");
	#endif

	cur_hide();

	while (1)
	{
		draw_box(1, 1, 30, 41, ROW, COL, '*');
		for (i = 0; i < NUM; i++)
		{
			draw_rect(ball[i].x, ball[i].y, ball[i].color, 10, ball[i].h, ball[i].w, ball[i].ch);
		}	
		fflush(NULL);

		for (i = 0; i < NUM; i++)
		{
			move(&ball[i].x, &ball[i].y, &ball[i].x_inc, &ball[i].y_inc, &ball[i].color, ball[i].h, ball[i].w);
		}
		usleep(200000);

	}
	cur_show();

	return 0;
}
