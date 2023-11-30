#include "shell.h"

/**
 * _is_cmd - determining whether a file is an exec. command
 * @info: the info structure.
 * @path: path to the file above
 *
 * Return: 1 if true, 0 otherwise always
 */
int _is_cmd(info_t *info, char *path)
{
	struct stat st;

	(void)info;
	if (!path || stat(path, &st))
		return (0);

	if (st.st_mode & S_IFREG)
	{
		return (1);
	}
	return (0);
}

/**
 * _dup_chars - duplicating char.s
 * @pathstr: the PATH string above
 * @start: start of index
 * @stop: stopp of index
 *
 * Return: ptr to new buffer
 */
char *_dup_chars(char *pathstr, int start, int stop)
{
	static char buf[1024];
	int j = 0, q = 0;

	for (q = 0, j = start; j < stop; ++j)
		if (pathstr[j] != ':')
			buf[++q] = pathstr[j];
	buf[q] = 0;
	return (buf);
}

/**
 * _find_path - finding the cmd in the PATH string
 * @info: the info structuture
 * @pathstr: the PATH string
 * @cmd: the command to find
 *
 * Return: absolute full path of cmd if found or NULL
 */
char *_find_path(info_t *info, char *pathstr, char *cmd)
{
	int i = 0, curr_pos = 0;
	char *path;

	if (!pathstr)
		return (NULL);
	if ((_str_len(cmd) > 2) && _starts_wth(cmd, "./"))
	{
		if (_is_cmd(info, cmd))
			return (cmd);
	}
	while (1)
	{
		if (!pathstr[i] || pathstr[i] == ':')
		{
			path = _dup_chars(pathstr, curr_pos, i);
			if (!*path)
				_str_cat(path, cmd);
			else
			{
				_str_cat(path, "/");
				_str_cat(path, cmd);
			}
			if (_is_cmd(info, path))
				return (path);
			if (!pathstr[i])
				break;
			curr_pos = i;
		}
		++i;
	}
	return (NULL);
}
