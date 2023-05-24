#include "shell.h"
/**
 * add_node_end - Adds at end of list
 * @h: head address
 * @s: string
 * @n: number node index
 * Return: sizeof list
 */
chain_t *add_node_end(chain_t **h, const char *s, int n)
{
	chain_t *new_node, *node;

	if (!h)
		return (NULL);
	node = *h;
	new_node = malloc(sizeof(chain_t));
	if (!new_node)
		return (NULL);
	_memset((void *)new_node, 0, sizeof(chain_t));
	new_node->num = n;
	if (s)
	{
		new_node->str = _strdup(s);
		if (!new_node->str)
		{
			free(new_node);
			return (NULL);
		}
	}
	if (node)
	{
		while (node->next)
			node = node->next;
		node->next = new_node;
	} else
		*h = new_node;
	return (new_node);
}
/**
 * add_node - Adds a node to list
 * @h: Head of list
 * @s: string
 * @n: number node index
 * Return: sizeof list
 */
chain_t *add_node(chain_t **h, const char *s, int n)
{
	chain_t *new_head;

	if (!h)
		return (NULL);
	new_head = malloc(sizeof(chain_t));
	if (!new_head)
		return (NULL);
	_memset((void *)new_head, 0, sizeof(chain_t));
	new_head->num = n;
	if (s)
	{
		new_head->str = _strdup(s);
		if (!new_head->str)
		{
			free(new_head);
			return (NULL);
		}
	}
	new_head->next = *h;
	*h = new_head;
	return (new_head);
}
/**
 * printListStr - Prints the string in a list
 * @h: head
 * Return: sizeof list
 */
size_t printListStr(const chain_t *h)
{
	size_t a = 0;

	while (h)
	{
		_puts(h->str ? h->str : "(nil)");
		_puts("\n");
		h = h->next;
		a++;
	}
	return (a);
}
/**
 * delete_node_at_index - Removes a node from list
 * @h: Head
 * @index: Index
 * Return: Bitwise true or false
 */
int delete_node_at_index(chain_t **h, unsigned int index)
{
	chain_t *node, *prev_node;
	unsigned int a = 0;

	if (!h || !*h)
		return (0);
	if (!index)
	{
		node = *h;
		*h = (*h)->next;
		free(node->str);
		return (1);
	}
	node = *h;
	while (node)
	{
		if (a == index)
		{
			prev_node->next = node->next;
			free(node->str);
			free(node);
			return (1);
		}
		a++;
		prev_node = node;
		node = node->next;
	}
	return (0);
}
/**
 * free_list - Frees entire list
 * @h: Head
 */
void free_list(chain_t **h)
{
	chain_t *node, *next_node, *hd;

	if (!h || !*h)
	{
		return;
	}
	hd = *h;
	node = hd;
	while (node)
	{
		next_node = node->next;
		free(node->str);
		free(node);
		node = next_node;
	}
	*h = NULL;
}
