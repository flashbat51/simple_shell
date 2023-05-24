#include "shell.h"
/**
 * _strchr - Finds letter in string
 * @str: string arg
 * @a: character arg
 * Return: pointer to character
 */
char *_strchr(char *str, char a)
{
	do {
		if (*str == a)
			return (str);
	} while (*(str++) != '\0');
	return (NULL);
}
/**
 * _strncat - string concatenater
 * @s1: first string
 * @s2: second string
 * @buf: buffer
 * Return: full string
 */
char *_strncat(char *s1, char *s2, int buf)
{
	char *a = s1;
	int b = 0, c = 0;

	while (s1[b] != '\0')
		b++;
	while (s2[c] != '\0' && c < buf)
		s1[b++] = s2[c++];
	if (c < buf)
		s1[b] = '\0';
	return (a);
}
/**
 * _strncpy - copies strings
 * @s1: to be copied
 * @s2: the copy
 * @buf: buffer
 * Return: copied string
 */
char *_strncpy(char *s1, char *s2, int buf)
{
	char *a = s1;
	int c, b = 0;

	while (s2[b] != '\0' && b < buf - 1)
	{
		s1[b] = s2[b];
		b++;
	}
	if (b < buf)
	{
		c = b;
		while (c < buf)
			s1[c++] = '\0';
	}
	return (a);
}
