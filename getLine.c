#include "shell.h"
/**
 * read_buf - reads buffer
 * @data: struct arg
 * @buf: buffer
 * @a: size
 * Return: buffer
 */
ssize_t read_buf(data_t *data, char *buf, size_t *a)
{
	ssize_t b = 0;
	if (*a)
		return (0);
	b = read(data->readfd, buf, READ_BUF_SIZE);
	if (b >= 0)
		*a = b;
	return (b);
}
/**
 * sigintHandler - ctrl C
 * @sigNum: Number of sig
 */
void sigintHandler(int sigNum __attribute__((unused)))
{
	_puts("\n");
	_puts("$ ");
	_putchar(BUF_FLUSH);
}
/**
 * _getline - fetch line from stdin
 * @data: struct arg
 * @p: pointer
 * @len: length
 * Return: string
 */
int _getline(data_t *data, char **p, size_t *len)
{
	ssize_t a = 0, b = 0;
	size_t c;
	char *d = NULL, *e = NULL, *f;
	static char buf[READ_BUF_SIZE];
	static size_t g, h;

	d = *p;
	if (d && len)
		b = *len;
	if (g == h)
		g = h = 0;
	a = read_buf(data, buf, &h);
	if (a == -1 || (a == 0 && h == 0))
		return (-1);
	f = _strchr(buf + g, '\n');
	c = f ? 1 + (unsigned int)(f - buf) : h;
	e = _realloc(d, b, b ? b + c : c + 1);
	if (!e)
		return (d ? free(d), -1 : -1);
	if (b)
		_strncat(e, buf + g, c - g);
	else
		_strncpy(e, buf + g, c - g + 1);
	b += c - g;
	g = c;
	d = e;
	if (len)
		*len = b;
	*p = d;
	return (b);
}
/* input_buf - For chaineed commands
 * @data: struct arg
 * @buff: buffer
 * @length: length of variable
 * Return: number of bytes
 */
ssize_t input_buf(data_t *data, char **buff, size_t *length)
{
	size_t len_p = 0;
	ssize_t ar = 0;

	if (!*length)
	{
		free(*buff);
		*buff = NULL;
		signal(SIGINT, sigintHandler);
#if USE_GETLINE
		ar = getline(buff, &len_p, stdin);
#else
		ar = _getline(data, buff, &len_p);
#endif
		if (ar > 0)
		{
			if ((*buff)[ar - 1] == '\n')
			{
				(*buff)[ar - 1] = '\0';
				ar--;
			}
			data->linecount_flag = 1;
			remove_comments(*buff);
			historyListBuild(data, *buff, data->histcount++);
			{
				*length = ar;
				data->cmd_buf = buff;
			}
		}
	}
	return (ar);
}
/**
 * get_input - Read input
 * @data: struct arg
 * Return: number of bytes
 */
ssize_t get_input(data_t *data)
{
	static size_t i, j, len;
	static char *buff;
	ssize_t ar = 0;
	char **buff_p = &(data->arg), *p;
	
	_putchar(BUF_FLUSH);
	ar = input_buf(data, &buff, &len);
	if (ar == -1)
		return (-1);
	if (len)
	{
		j = i;
		p = buff + i;
		check_chain(data, buff, &j, i, len);
		while (j < len)
		{
			if (is_chain(data, buff, &j))
				break;
			j++;
		}
		i = j + 1;
		if (i >= len)
		{
			i = len = 0;
			data->cmd_buf_type = CMD_NORM;
		}
		*buff_p = p;
		return (_strlen(p));
	}
	*buff_p = buff;
	return (ar);
}
