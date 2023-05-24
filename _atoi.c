#include "shell.h"
/**
 * is_delim - Delimeter checker
 * @c: Character to check
 * @delim: String with delimeter
 * Return: Bitwise true or false
 */
int is_delim(char c, char *delim)
{
	while (*delim != '\0')
		if (*delim++ == c)
			return (1);
	return (0);
}
/**
 * interactive - Interactive mode activator
 * @data: address of struct
 * Return: Bitwise true or false
 */
int interactive(data_t *data)
{
	return (isatty(STDIN_FILENO) && data->readfd <= 2);
}
/**
 * _atoi - Mimics array char to integer
 * @s: string or array char to be converted
 * Return: Integer
 */
int _atoi(char *s)
{
	unsigned int res = 0;
	int a, b = 1, flg = 0, opt;

	for (a = 0; s[a] != '\0' && flg != 2; a++)
	{
		if (s[a] == '-')
			b = b * -1;
		if (s[a] >= '0' && s[a] <= '9')
		{
			flg = 1;
			res = res * 10;
			res = res + (s[a] - '0');
		} else if (flg == 1)
			flg = 2;
	}
	if (b == -1)
		opt = -res;
	else
		opt = res;
	return (opt);
}
/**
 * _isalpha - Checks for alphabets
 * @a: Character arg
 * Return: Bitwise true or false
 */
int _isalpha(int a)
{
	if ((a >= 'a' && a <= 'z') || (a >= 'A' && a <= 'Z'))
		return (1);
	return (0);
}
