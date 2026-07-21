#include <stdio.h>
#include <stdarg.h>
#include <string.h>
#include <stdlib.h>


//函数声明
void str_copy(char dest[], char src[]);
void str_copy_num(char dest[], char src[], int num);
void str_cat(char dest[], char src[]);
void str_cat_num(char dest[], char src[], int num);
int str_cmp(char s1[], char s2[]);
int str_cmp_num(char s1[], char s2[], int num);
int str_chr_first(char s[], char ch);
int str_chr_end(char s[], char ch);

int main(void)
{
	char dest[128] = "AAAAAAAAAAAAAA";
	char src[128] = "hello";

	printf("str_chr_first(hello, l) : %d\n", str_chr_first("hello", 'l'));

	#if 0
	/*printf("main : src : %s %p\n", src, src);*/
	printf("dest : %s\n", dest);
	str_copy(dest, src);
	/*str_copy_num(dest, src, 2);*/
	printf("dest : %s\n", dest);

	str_cat(dest, "world");
	//数组脱离开定义不可以整体赋值
	/*dest = "BBBBBBBB";*/
	/*str_copy(dest, "BBBBBBBBBBBB");*/
	printf("dest : %s\n", dest);

	#endif

    /*
	 *printf("str_cmp(make, mask) = %d\n", str_cmp("make", "mask"));
	 *printf("str_cmp(make, make) = %d\n", str_cmp("make", "make"));
	 *printf("str_cmp(mask, make) = %d\n", str_cmp("mask", "make"));
	 *printf("str_cmp(makee, make) = %d\n", str_cmp("makee", "make"));
     */


	return 0;
}
void str_copy(char dest[], char src[])
{
	int i = 0;

	while ((dest[i] = src[i++]) != '\0')
		;
    /*
	 *while (src[i] != '\0')
	 *{
	 *    dest[i] = src[i];
	 *    i++;
	 *}
	 *dest[i] = '\0';
     */
    /*
	 *printf("copy => dest : %s\n", dest);
	 *printf("copy => src : %s %p %p\n", src, src, &src);
	 *dest = src;
	 *printf("copy => dest : %s\n", dest);
     */
}
void str_copy_num(char dest[], char src[], int num)
{
	int i = 0;

	while ((dest[i] = src[i++]) != '\0' && --num)
		;
}
void str_cat(char dest[], char src[])
{
	int len = strlen(dest);
	int i = 0;

	while ((dest[len + i] = src[i++]) != '\0')
		;
	/*str_copy(dest + len, src);*/
}
void str_cat_num(char dest[], char src[], int num)
{

}
int str_cmp(char s1[], char s2[])
{
	int i = 0, ret;

	while ((s1[i] == s2[i]) && s1[i] != '\0' && s2[i] != '\0')
	{
		i++;
	}

	ret = s1[i] - s2[i];
	if (ret > 0)
		return 1;
	else if (ret < 0)
		return -1;
	else
		return 0;
}
int str_cmp_num(char s1[], char s2[], int num)
{

}
int str_chr_first(char s[], char ch)
{
	int i  = 0;

	while (s[i] != '\0')
	{
		if (s[i] == ch)
			return i;
		i++;
	}

	return -1;
}
int str_chr_end(char s[], char ch)
{

}
