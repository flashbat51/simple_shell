#include "shell.h"
/**
 * free_info - frees data_t fields
 * @data: struct arg
 * @all: true or false
 */
void free_info(data_t *data, int all)
{
	ffree(data->argv);
	data->argv = NULL;
	data->path = NULL;
	if (all)
	{
		if (!data->cmd_buf)
			free(data->arg);
		if (data->env)
			free_list(&(data->env));
		if (data->history)
			free_list(&(data->history));
		if (data->alias)
			free_list(&(data->alias));
		ffree(data->environ);
		data->environ = NULL;
		bfree((void **)data->cmd_buf);
		if (data->readfd > 2)
			close(data->readfd);
		_putchar(BUF_FLUSH);
	}
}
/**
 * set_info - Struct start up
 * @data: struct arg
 * @av: vector
 */
void set_info(data_t *data, char **av)
{
	int a = 0;

	data->fname = av[0];
	if (data->arg)
	{
		data->argv = strtow(data->arg, " \t");
		if (!data->argv)
		{
			data->argv = malloc(sizeof(char *) * 2);
			if (data->argv)
			{
				data->argv[0] = _strdup(data->arg);
				data->argv[1] = NULL;
			}
		}
		for (a = 0; data->argv && data->argv[a]; a++)
			;
		data->argc = a;
		replace_alias(data);
		replace_vars(data);
	}
}
/**
 * clear_info - reset struct
 * @data: struct arg
 */
void clear_info(data_t *data)
{
	data->arg = NULL;
	data->argv = NULL;
	data->path = NULL;
	data->argc = 0;
}
