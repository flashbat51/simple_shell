#include "shell.h"
/**
 * printEnv - Prints environment
 * @data: struct arg
 * Return: 0
 */
int printEnv(data_t *data)
{
	printListStr(data->env);
	return (0);
}
/**
 * envGet - Gets environment
 * @data: struct arg
 * @name: variable name
 * Return: resulting value
 */
char *envGet(data_t *data, const char *name)
{
	chain_t *node = data->env;
	char *a;

	while (node)
	{
		a = starts_with(node->str, name);
		if (a && *a)
			return (a);
		node = node->next;
	}
	return (NULL);
}
/**
 * envList - makes env List
 * @data: struct arg
 * Return: 0
 */
int envList(data_t *data)
{
	size_t a;
	chain_t *node = NULL;

	for (a = 0; environ[a]; a++)
		add_node_end(&node, environ[a], 0);
	data->env = node;
	return (0);
}
/**
 * unsetEnv - deletes env variable
 * @data: struct arg
 * Return: 0
 */
int _unsetenv(data_t *data)
{
	int a;

	if (data->argc == 1)
	{
		_eputs("A lot of arguments.\n");
		return (1);
	}
	for (a = 1; a <= data->argc; a++)
		unsetEnv(data, data->argv[a]);
	return (0);
}
/**
 * setEnv - creates env variable
 * @data: struct arg
 * Return: 0
 */
int setEnv(data_t *data)
{
	if (data->argc != 3)
	{
		_eputs("Wrong number of arguments.\n");
		return (1);
	}
	if (_setEnv(data, data->argv[1], data->argv[2]))
		return (0);
	return (1);
}
