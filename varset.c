#include "shell.h"

/**
 * is_chain - to test if current character
 * in buffer is a chain delimeter
 * @data: the parameter struct
 * @buf: the char buffer
 * @p: address of current position in buf
 * Return: 1 if chain delimeter, 0 otherwise
 */
int is_chain(data_t *data, char *buf, size_t *p)
{
	size_t j = *p;

	if (buf[j] == '|' && buf[j + 1] == '|')
	{
		buf[j] = 0;
		j++;
		data->cmd_buf_type = CMD_OR;
	}
	else if (buf[j] == '&' && buf[j + 1] == '&')
	{
		buf[j] = 0;
		j++;
		data->cmd_buf_type = CMD_AND;
	}
	else if (buf[j] == ';') /* found end of this command */
	{
		buf[j] = 0; /* replace semicolon with null */
		data->cmd_buf_type = CMD_CHAIN;
	}
	else
		return (0);
	*p = j;
	return (1);
}


/**
 * check_chain - checks chaining based on last status
 * @data: the parameter structure
 * @buf: the char buffer
 * @p: current address position in buf
 * @i: starting position in buf
 * @len: length of buf
 * Return: Void
 */
void check_chain(data_t *data, char *buf, size_t *p, size_t i, size_t len)
{
	size_t j = *p;

	if (data->cmd_buf_type == CMD_AND)
	{
		if (data->status)
		{
			buf[i] = 0;
			j = len;
		}
	}
	if (data->cmd_buf_type == CMD_OR)
	{
		if (!data->status)
		{
			buf[i] = 0;
			j = len;
		}
	}

	*p = j;
}

/**
 * replace_alias - replace aliases in the tokened string
 * @data: the parameter structure
 * Return: 1 if replaced, 0 otherwise
 */
int replace_alias(data_t *data)
{
	int i;
	chain_t *node;
	char *p;

	for (i = 0; i < 10; i++)
	{
		node = node_starts_with(data->alias, data->argv[0], '=');
		if (!node)
			return (0);
		free(data->argv[0]);
		p = _strchr(node->str, '=');
		if (!p)
			return (0);
		p = _strdup(p + 1);
		if (!p)
			return (0);
		data->argv[0] = p;
	}
	return (1);
}

/**
 * replace_vars - replace vars in the tokened string
 * @data: the parameter structure
 * Return: 1 if replaced, 0 otherwise
 */

int replace_vars(data_t *data)
{
	int i = 0;
	chain_t *node;

	for (i = 0; data->argv[i]; i++)
	{
		if (data->argv[i][0] != '$' || !data->argv[i][1])
			continue;

		if (!_strcmp(data->argv[i], "$?"))
		{
			replace_string(&(data->argv[i]),
					_strdup(convert_number(data->status, 10, 0)));
			continue;
		}
		if (!_strcmp(data->argv[i], "$$"))
		{
			replace_string(&(data->argv[i]),
					_strdup(convert_number(getpid(), 10, 0)));
			continue;
		}
		node = node_starts_with(data->env, &data->argv[i][1], '=');
		if (node)
		{
			replace_string(&(data->argv[i]),
					_strdup(_strchr(node->str, '=') + 1));
			continue;
		}
		replace_string(&data->argv[i], _strdup(""));

	}
	return (0);
}


/**
 * replace_string - to replace string
 * @old: old string address
 * @new: new string
 * Return: 1 if replaced, 0 otherwise
 */
int replace_string(char **old, char *new)
{
	free(*old);
	*old = new;
	return (1);
}
