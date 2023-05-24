#include "shell.h"
/**
 * _putfd - writes into file descriptor
 * @c: character arg
 * @fd: file descriptor arg
 * Return: 1 or -1
 */
int _putfd(char c, int fd)
{
	static char buf[WRITE_BUF_SIZE];
	static int a;

	if (c == BUF_FLUSH || a >= WRITE_BUF_SIZE)
	{
		write(fd, buf, a);
		a = 0;
	}
	if (c != BUF_FLUSH)
		buf[a++] = c;
	return (1);
}
/**
 * _putsfd - Prints input string
 * @str: string arg
 * @fd: file descriptor arg
 * Return: Number of chars
 */
int _putsfd(char *str, int fd)
{
	int a = 0;

	if (!str)
		return (0);
	while (*str)
		a += _putfd(*(str++), fd);
	return (a);
}
/**
 * _eputchar - writes char to stderr
 * @c: char arg
 * Return: 1 or -1
 */
int _eputchar(char c)
{
	static char buf[WRITE_BUF_SIZE];
	static int a;

	if (c == BUF_FLUSH || a >= WRITE_BUF_SIZE)
	{
		write(2, buf, a);
		a = 0;
	}
	if (c != BUF_FLUSH)
		buf[a++] = c;
	return (1);
}
/**
 * _eputs - prints input string
 * @str: string arg
 */
void _eputs(char *str)
{
	int a = 0;

	if (!str)
		return;
	while (str[a] != '\0')
		_eputchar(str[a++]);
}
