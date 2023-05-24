#include "shell.h"
/**
 * print_alias - Prints alias
 * @node: node arg
 * Return: Bitwise true or false
 */
int print_alias(chain_t *node)
{
	char *a = NULL, *b = NULL;
	
	if (node)
	{
		a = _strchr(node->str, '=');
		for (b = node->str; b <= a; b++)
			_putchar(*b);
		_putchar('\'');
		_puts(a + 1);
		_puts("'\n");
		return (0);
	}
	return (1);
}
/**
 * unset_alias - clears alias
 * @data: struct arg
 * @str: string arg
 * Return: Bitwise true or false
 */
int unset_alias(data_t *data, char *str)
{
	char *a, b;
	int res;

	a = _strchr(str, '=');
	if (!a)
		return (1);
	b = *a;
	*a = 0;
	res = delete_node_at_index(&(data->alias),
			get_node_index(data->alias, node_starts_with(data->alias, str, -1)));
	*a = b;
	return (res);
}
/**
 * printHistory - Print History
 * @data: Struct arg
 * Return: 0
 */
int printHistory(data_t *data)
{
	printList(data->history);
	return (0);
}
/**
 * set_alias - Set alias
 * @data: struct arg
 * @str: string arg
 * Return: Bitwise true or false
 */
int set_alias(data_t *data, char *str)
{
	char *a;

	a = _strchr(str, '=');
	if (!a)
		return (1);
	if (!*(++a))
		return (unset_alias(data, str));
	unset_alias(data, str);
	return (add_node_end(&(data->alias), str, 0) == NULL);
}
/**
 * _alias - man alias copy
 * @data: struct arg
 * Return: 0
 */
int _alias(data_t *data)
{
	char *a = NULL;
	chain_t *node = NULL;
	int b = 0;

	if (data->argc == 1)
	{
		node = data->alias;
		while (node)
		{
			print_alias(node);
			node = node->next;
		}
		return (0);
	}
	for (b = 1; data->argv[b]; b++)
	{
		a = _strchr(data->argv[b], '=');
		if (a)
			set_alias(data, data->argv[b]);
		else
			print_alias(node_starts_with(data->alias,
						data->argv[b], '='));
	}
	return (0);
}
