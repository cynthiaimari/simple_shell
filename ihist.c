#include "shell.h"

/**
 * _get_history_file - getting the hist. file
 * @info: param structure item
 *
 * Return: allocated string with hist. file
 */

char *_get_history_file(info_t *info)
{
	char *buf, *dir;

	dir = _gitenv(info, "HOME=");
	if (!dir)
		return (NULL);
	buf = malloc(sizeof(char) * (_str_len(dir) + _str_len(HIST_FILE) + 2));
	if (!buf)
		return (NULL);
	buf[0] = 0;
	_str_cpy(buf, dir);
	_str_cat(buf, "/");
	_str_cat(buf, HIST_FILE);
	return (buf);
}

/**
 * _write_history - creating a file, or appends to an existing file
 * @info: the param structure
 *
 * Return: 1 on success, otherwise -1
 */
int _write_history(info_t *info)
{
	ssize_t fd;
	char *filename = _get_history_file(info);
	list_t *node = NULL;

	if (!filename)
		return (-1);

	fd = open(filename, O_CREAT | O_TRUNC | O_RDWR, 0644);
	free(filename);
	if (fd == -1)
		return (-1);
	for (node = info->history; node; node = node->next)
	{
		_putsfd(node->str, fd);
		_putfd('\n', fd);
	}
	_putfd(BUF_FLUSH, fd);
	close(fd);
	return (1);
}

/**
 * _read_history - reading hist. from file
 * @info: the param structure
 *
 * Return: to return hist-count on success, 0 if otherwise
 */
int _read_history(info_t *info)
{
	int i, last = 0, linecount = 0;
	ssize_t fd, rdlen, fsize = 0;
	struct stat st;
	char *buf = NULL, *filename = _get_history_file(info);

	if (!filename)
		return (0);

	fd = open(filename, O_RDONLY);
	free(filename);
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
			_build_history_list(info, buf + last, linecount++);
			last = i + 1;
		}
	if (last != i)
		_build_history_list(info, buf + last, linecount++);
	free(buf);
	info->histcount = linecount;
	while (info->histcount-- >= HIST_MAX)
		_delete_node_at_index(&(info->history), 0);
	_re_number_history(info);
	return (info->histcount);
}

/**
 * _build_history_list - adding entry to a hist linked list
 * @info: Structure containing potent. arg.s. Used to maintain
 * @buf: buffer
 * @linecount: the hist line-count, hist-count
 *
 * Return: Always return 0
 */
int _build_history_list(info_t *info, char *buf, int linecount)
{
	list_t *node = NULL;

	if (info->history)
		node = info->history;
	_add_node_end(&node, buf, linecount);

	if (!info->history)
		info->history = node;
	return (0);
}

/**
 * _re_number_history - renumbering the hist. linked list after changes
 * @info: Struct containing potent arg'ts. Used to maintain
 *
 * Return: the new hist-count item
 */
int _re_number_history(info_t *info)
{
	list_t *node = info->history;
	int k = 0;

	while (node)
	{
		node->num = ++k;
		node = node->next;
	}
	return (info->histcount = k);
}
