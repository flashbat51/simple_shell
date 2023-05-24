#include "shell.h"

/**
 * hsh - shell loop for hsh
 * @data: accept the parameter & return data struct
 * @av: the argument vector from main()
 * Return: 0 on success, 1 on error or error code
 */
int hsh(data_t *data, char **av)
{
	ssize_t r = 0;
	int builtin_ret = 0;

	while (r != -1 && builtin_ret != -2)
	{
		clear_info(data);
		if (interactive(data))
			_puts("$ ");
		_eputchar(BUF_FLUSH);
		r = get_input(data);
		if (r != -1)
		{
			set_info(data, av);
			builtin_ret = find_builtin(data);
			if (builtin_ret == -1)
				find_cmd(data);
		}
		else if (interactive(data))
			_putchar('\n');
		free_info(data, 0);
	}
	historyWrite(data);
	free_info(data, 1);
	if (!interactive(data) && data->status)
		exit(data->status);
	if (builtin_ret == -2)
	{
		if (data->err_num == -1)
			exit(data->status);
		exit(data->err_num);
	}
	return (builtin_ret);
}

/**
 * find_builtin - find a builtin command
 * @data: the parameter & return data struct
 * Return: -1 if builtin not found,
 * 0 if builtin executed successfully,
 * 1 if builtin found but not successful,
 * -2 if builtin signals exit()
 */
int find_builtin(data_t *data)
{
	int i, built_in_ret = -1;
	builtin_t builtintbl[] = {
		{"exit", shellExit},
		{"env", printEnv},
		{"help", helpCall},
		{"history", printHistory},
		{"setenv", setEnv},
		{"unsetenv", _unsetenv},
		{"cd", chDir},
		{"alias", _alias},
		{NULL, NULL}
	};

	for (i = 0; builtintbl[i].type; i++)
		if (_strcmp(data->argv[0], builtintbl[i].type) == 0)
		{
			data->line_count++;
			built_in_ret = builtintbl[i].func(data);
			break;
		}
	return (built_in_ret);
}


/**
 * find_cmd - finds command in PATH
 * @data: the parameter & return data struct
 * Return: void
 */
void find_cmd(data_t *data)
{
	char *path = NULL;
	int i, k;

	data->path = data->argv[0];
	if (data->linecount_flag == 1)
	{
		data->line_count++;
		data->linecount_flag = 0;
	}
	for (i = 0, k = 0; data->arg[i]; i++)
		if (!is_delim(data->arg[i], " \t\n"))
			k++;
	if (!k)
		return;
	path = find_path(data, envGet(data, "PATH="), data->argv[0]);
	if (path)
	{
		data->path = path;
		fork_cmd(data);
	}
	else
	{
		if ((interactive(data) || envGet(data, "PATH=")
			|| data->argv[0][0] == '/') && is_cmd(data, data->argv[0]))
			fork_cmd(data);
		else if (*(data->arg) != '\n')
		{
			data->status = 127;
			print_error(data, "not found\n");
		}
	}
}


/**
 * fork_cmd - forks an exec thread to run cmd
 * @data: the parameter & return data struct
 * Return: void
 */
void fork_cmd(data_t *data)
{
	pid_t child_pid;

	child_pid = fork();
	if (child_pid == -1)
	{
		/* TODO: PUT ERROR FUNCTION */
		perror("Error:");
		return;
	}
	if (child_pid == 0)
	{
		if (execve(data->path, data->argv, environGet(data)) == -1)
		{
			free_info(data, 1);
			if (errno == EACCES)
				exit(126);
			exit(1);
		}
		/* TODO: PUT ERROR FUNCTION */
	}
	else
	{
		wait(&(data->status));
		if (WIFEXITED(data->status))
		{
			data->status = WEXITSTATUS(data->status);
			if (data->status == 126)
				print_error(data, "Permission denied\n");
		}
	}
}
