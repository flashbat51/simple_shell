#include "shell.h"
/**
 * get_node_index - Gets node index
 * @h: Head
 * @node: Node
 * Return: Index of node
 */
ssize_t get_node_index(chain_t *h, chain_t *node)
{
	size_t a = 0;

	while (h)
	{
		if (h == node)
			return (a);
		h = h->next;
		a++;
	}
	return (-1);
}
/**
 * node_starts_with - Node with that identifier is returned
 * @node: Node
 * @prefix: prefix
 * @c: character after prefix
 * Return: Node
 */
chain_t *node_starts_with(chain_t *node, char *prefix, char c)
{
	char *ap = NULL;

	while (node)
	{
		ap = starts_with(node->str, prefix);
		if (ap && ((c == -1) || (*ap == c)))
			return (node);
		node = node->next;
	}
	return (NULL);
}
/**
 * printList - Prints entire list
 * @h: Head
 * Return: sizeof list
 */
size_t printList(const chain_t *h)
{
	size_t a = 0;

	while (h)
	{
		_puts(convert_number(h->num, 10, 0));
		_putchar(':');
		_putchar(' ');
		_puts(h->str ? h->str : "(nil)");
		_puts("\n");
		h = h->next;
		a++;
	}
	return (a);
}
/**
 * list_to_strings - extracts the string in list
 * @h: Head
 * Return: string
 */
char **list_to_strings(chain_t *h)
{
	chain_t *node = h;
	size_t i = list_len(h), j;
	char **strs, *str;

	if (!h || !i)
		return (NULL);
	strs = malloc(sizeof(char *) * (i + 1));
	if (!strs)
		return (NULL);
	for (i = 0; node; node = node->next, i++)
	{
		str = malloc(_strlen(node->str) + 1);
		if (!str)
		{
			for (j = 0; j < i; j++)
				free(strs[j]);
			free(strs);
			return (NULL);
		}
		str = _strcpy(str, node->str);
		strs[i] = str;
	}
	strs[i] = NULL;
	return (strs);
}
/**
 * list_len - Solves length of list
 * @h: pointer to head
 * Return: sizeof list
 */
size_t list_len(const chain_t *h)
{
	size_t a = 0;

	while (h)
	{
		h = h->next;
		a++;
	}
	return (a);
}
