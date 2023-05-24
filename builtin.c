#include "shell.h"
/**
 * shellExit - Exits shell
 * @data: Struct with arg and func
 * Return: Exits and returns appropriate flag
 */
int shellExit(data_t *data)
{
	int checkExit;

	if (data->argv[1])
	{
		checkExit = _erratoi(data->argv[1]);
		if (checkExit == -1)
		{
			data->status = 2;
			print_error(data, "An incorrect Number: ");
			_eputs(data->argv[1]);
			_eputchar('\n');
			return (1);
		}
		data->err_num = _erratoi(data->argv[1]);
		return (-2);
	}
	data->err_num = -1;
	return (-2);
}
/**
 * chDir - Change directory
 * @data: Struch with arg and func
 * Return: 0
 */
int chDir(data_t *data)
{
	int chDirRes;
	char buf[1024], *a, *dir;

	a = getcwd(buf, 1024);
	if (!a)
		_puts("TODO: >> Failure Msg Here <<\n");
	if (!data->argv[1])
	{
		dir = envGet(data, "HOME=");
		if (!dir)
			chDirRes =
				chdir((dir = envGet(data, "PWD=")) ? dir : "/");
		else
			chDirRes = chdir(dir);
	} else if (_strcmp(data->argv[1], "-") == 0)
	{
		if (!envGet(data, "OLDPWD="))
		{
			_puts(a);
			_putchar('\n');
			return (1);
		}
		_puts(envGet(data, "OLDPWD="));
		_putchar('\n');
		chDirRes = chdir((dir = envGet(data, "OLDPWD=")) ? dir : "/");
	} else
		chDirRes = chdir(data->argv[1]);
	if (chDirRes == -1)
	{
		print_error(data, "Can't change directory to ");
		_eputs(data->argv[1]);
		_eputchar('\n');
	} else
	{
		_setEnv(data, "OLDPWD", envGet(data, "PWD="));
		_setEnv(data, "PWD", getcwd(buf, 1024));
	}
	return (0);
}
/**
 * helpCall - Help process
 * @data: arg
 * Return: 0
 */
int helpCall(data_t *data)
{
	char **array;

	array = data->argv;
	_puts("Call to help executes, Func not implemented yet\n");
	if (0)
		_puts(*array);
	return (0);
}
