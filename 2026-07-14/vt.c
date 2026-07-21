#include "vt.h"

//函数声明
void gotoxy(int x, int y)
{
	printf("\033[%d;%dH", x, y);
}
void putch(int x, int y, int fcolor, int bcolor, char ch)
{
	gotoxy(x, y);
	printf("\033[%d;%dm%c\033[0m", fcolor, bcolor, ch);
}
void putstr(int x, int y, int fcolor, int bcolor, char *s)
{
	gotoxy(x, y);
	printf("\033[%d;%dm%s\033[0m", fcolor, bcolor, s);

}
void move_up(int num)
{
	printf("\033[%dA", num);
}
void move_down(int num)
{
	printf("\033[%dB", num);
}
void move_left(int num)
{
	printf("\033[%dD", num);
}
void move_right(int num)
{
	printf("\033[%dC", num);

}
void cur_save(void)
{
	printf("\033[s");
}
void cur_load(void)
{
	printf("\033[u");
}
void cur_hide(void)
{
	printf("\033[?25l");
}
void cur_show(void)
{
	printf("\033[?25h");
}
void draw_horizontal(int x, int y, int fcolor, int bcolor, int len, char ch)
{
	int i;
	gotoxy(x, y);
	for (i = 0; i < len; i++)
	{
		printf("\033[%d;%dm%c\033[0m", fcolor, bcolor, ch);
	}
}
void draw_vertical(int x, int y, int fcolor, int bcolor, int len, char ch)
{
	int i;
	for (i = 0; i < len; i++)
	{
		gotoxy(x + i, y);
		printf("\033[%d;%dm%c\033[0m", fcolor, bcolor, ch);
	}

}
void draw_box(int x, int y, int fcolor, int bcolor, int h, int w, char ch)
{
	int i, j;
	
	for (i = 0; i < h; i++)
	{
		gotoxy(x + i, y);
		for (j = 0; j < w; j++)
		{
			if (i == 0 || i == h - 1 || j == 0 || j == w - 1)
			{
				printf("\033[%d;%dm%c\033[0m", fcolor, bcolor, ch);
			}
			else
			{
				putchar(' ');
			}
		}
	}
}
void draw_rect(int x, int y, int fcolor, int bcolor, int h, int w, char ch)
{
	int i, j;
	
	for (i = 0; i < h; i++)
	{
		gotoxy(x + i, y);
		for (j = 0; j < w; j++)
		{
			printf("\033[%d;%dm%c\033[0m", fcolor, bcolor, ch);
		}
	}

}




