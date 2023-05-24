#include "shell.h"
/**
 * remove_comments - removes comments
 * @buf: string arg
 */
void remove_comments(char *buf)
{
	int a;

	for (a = 0; buf[a] != '\0'; a++)
	{
		if (buf[a] == '#' && (!a || buf[a - 1] == ' '))
		{
			buf[a] = '\0';
			break;
		}
	}
}
/**
 * convert_number - imitates itoa
 * @dig: digit arg
 * @bs: base arg
 * @flg: flag arg
 * Return: The string
 */
char *convert_number(long int dig, int bs, int flg)
{
	static char buf[50], *array;
	unsigned long digg = dig;
	char s = 0, *ptr;

	if (!(flg & CONVERT_UNSIGNED) && dig < 0)
	{
		digg = -dig;
		s = '-';
	}
	ptr = &buf[49];
	array = flg & CONVERT_LOWERCASE ? "0123456789abcdef" : "0123456789ABCDEF";
	*ptr = '\0';
	do {
		*(--ptr) = array[digg % bs];
		digg /= bs;
	} while (digg != 0);
	if (s)
	{
		*(--ptr) = s;
	}
	return (ptr);
}
/**
 * print_d - prints in decimal
 * @inp: arg
 * @fd: file descriptor
 * Return: number of prints
 */
int print_d(int inp, int fd)
{
	unsigned int _abs_, now;
	int (*__putchar)(char) = _putchar;
	int a, cnt = 0;

	if (fd == STDERR_FILENO)
		__putchar = _eputchar;
	if (inp < 0)
	{
		_abs_ = -inp;
		__putchar('-');
		cnt++;
	} else
		_abs_ = inp;
	now = _abs_;
	for (a = 1000000000; a > 1; a /= 10)
	{
		if (_abs_ / a)
		{
			__putchar('0' + now / a);
			cnt++;
		}
		now %= a;
	}
	__putchar('0' + now);
	cnt++;
	return (cnt);
}
/**
 * print_error - print error msg
 * @data: struct arg
 * @est: error type in string
 * Return: 0 or -1
 */
void print_error(data_t *data, char *est)
{
	_eputs(data->fname);
	_eputs(": ");
	print_d(data->line_count, STDERR_FILENO);
	_eputs(": ");
	_eputs(data->argv[0]);
	_eputs(": ");
	_eputs(est);
}
/**
 * _erratoi - string to integer
 * @s: string arg
 * Return: 0 or -1
 */
int _erratoi(char *s)
{
	unsigned long int res = 0;
	int a;

	if (*s == '+')
	{
		s++;
	}
	for (a = 0; s[a] != '\0'; a++)
	{
		if (s[a] >= '0' && s[a] <= '9')
		{
			res *= 10;
			res += (s[a] - '0');
			if (res > INT_MAX)
				return (-1);
		} else
			return (-1);
	}
	return (res);
}
