#include "shell.h"
/**
 * _setEnv - Sets up a new environment
 * @data: struct arg
 * @var: variable arg
 * @value: values of arg
 * Return: 0
 */
int _setEnv(data_t *data, char *var, char *value)
{
	char *a, *buf = NULL;
	chain_t *node;

	if (!var || !value)
		return (0);
	buf = malloc(_strlen(var) + _strlen(value) + 2);
	if (!buf)
		return (1);
	_strcpy(buf, var);
	_strcat(buf, "=");
	_strcat(buf, value);
	node = data->env;
	while (node)
	{
		a = starts_with(node->str, var);
		if (a && *a == '=')
		{
			free(node->str);
			node->str = buf;
			data->env_changed = 1;
			return (0);
		}
		node = node->next;
	}
	add_node_end(&(data->env), buf, 0);
	free(buf);
	data->env_changed = 1;
	return (0);
}
/**
 * environGet - Gets properties of an environment
 * @data: struct arg
 * Return: 0
 */
char **environGet(data_t *data)
{
	if (!data->environ || data->env_changed)
	{
		data->environ = list_to_strings(data->env);
		data->env_changed = 0;
	}
	return (data->environ);
}
/**
 * unsetEnv - Deletes variable of an environment
 * @data: struct arg
 * @var: variable arg
 * Return: Bitwise true or false
 */
int unsetEnv(data_t *data, char *var)
{
	size_t a = 0;
	chain_t *node = data->env;
	char *b;

	if (!node || !var)
		return (0);
	while (node)
	{
		b = starts_with(node->str, var);
		if (b && *b == '=')
		{
			data->env_changed = delete_node_at_index(&(data->env), a);
			a = 0;
			node = data->env;
			continue;
		}
		node = node->next;
		a++;
	}
	return (data->env_changed);
}
