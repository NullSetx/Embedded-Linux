#ifndef __VT_H__
#define __VT_H__

#include <stdio.h>
#include <string.h>
//函数声明
extern void gotoxy(int x, int y);
extern void putch(int x, int y, int fcolor, int bcolor, char ch);
extern void putstr(int x, int y, int fcolor, int bcolor, char *s);
extern void move_up(int num);
extern void move_down(int num);
extern void move_left(int num);
extern void move_right(int num);
extern void cur_save(void);
extern void cur_load(void);
extern void cur_hide(void);
extern void cur_show(void);
//画水平线
extern void draw_horizontal(int x, int y, int fcolor, int bcolor, int len, char ch);
//画垂直
extern void draw_vertical(int x, int y, int fcolor, int bcolor, int len, char ch);
extern void draw_box(int x, int y, int fcolor, int bcolor, int h, int w, char ch);
extern void draw_rect(int x, int y, int fcolor, int bcolor, int h, int w, char ch);


#endif //VT_H


