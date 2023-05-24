#include "shell.h"
/**
 * historyWrite - Writes the history
 * @data: struct arg
 * Return: Bitwise true or false
 */
int historyWrite(data_t *data)
{
	char *file = historyFileGet(data);
	chain_t *node = NULL;
	ssize_t fd;

	if (!file)
		return (-1);
	fd = open(file, O_CREAT | O_TRUNC | O_RDWR, 0644);
	free(file);
	if (fd == -1)
		return (-1);
	for (node = data->history; node; node = node->next)
	{
		_putsfd(node->str, fd);
		_putfd('\n', fd);
	}
	_putfd(BUF_FLUSH, fd);
	close(fd);
	return (1);
}
/**
 * historyRead - Reads from history
 * @data: struct arg
 * Return: count of history
 */
int historyRead(data_t *data)
{
	char *buf = NULL, *file = historyFileGet(data);
	struct stat st;
	ssize_t fd, rdlen, fsize = 0;
	int i, last = 0, linecount = 0;

	if (!file)
		return (0);
	fd = open(file, O_RDONLY);
	free(file);
	if (fd == -1)
		return (0);
	if (!fstat(fd, &st))
		fsize = st.st_size;
	if (fsize < 2)
		return (0);
	buf = malloc(sizeof(char) * (fsize + 1));
	if (!buf)
		return (0);
	rdlen = read(fd, buf, fsize);
	buf[fsize] = 0;
	if (rdlen <= 0)
		return (free(buf), 0);
	close(fd);
	for (i = 0; i < fsize; i++)
		if (buf[i] == '\n')
		{
			buf[i] = 0;
			historyListBuild(data, buf + last, linecount++);
			last = i + 1;
		}
	if (last != i)
		historyListBuild(data, buf + last, linecount++);
	free(buf);
	data->histcount = linecount;
	while (data->histcount-- >= HIST_M)
		delete_node_at_index(&(data->history), 0);
	historyRenumber(data);
	return (data->histcount);
}
/**
 * historyListBuild - Adds to history list
 * @data: struct arg
 * @buf: buffer
 * @linecount: history linecount
 * Return: 0
 */
int historyListBuild(data_t *data, char *buf, int linecount)
{
	chain_t *node = NULL;

	if (data->history)
		node = data->history;
	add_node_end(&node, buf, linecount);
	if (!data->history)
		data->history = node;
	return (0);
}
/**
 * historyRenumber - Renumbes the history
 * @data: struct arg
 * Return: history count
 */
int historyRenumber(data_t *data)
{
	int a = 0;
	chain_t *node = data->history;

	while (node)
	{
		node->num = a++;
		node = node->next;
	}
	return (data->histcount = a);
}
/**
 * historyFileGet - Gets history file
 * @data: struct arg
 * Return: string
 */
char *historyFileGet(data_t *data)
{
	char *dir, *buf;

	dir = envGet(data, "HOME=");
	if (!dir)
		return (NULL);
	buf = malloc(sizeof(char) * (_strlen(dir) + _strlen(HIST_F) + 2));
	buf[0] = 0;
	_strcpy(buf, dir);
	_strcat(buf, "/");
	_strcat(buf, HIST_F);
	return (buf);
}
