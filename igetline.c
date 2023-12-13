#include "shell.h"

/**
 * _input_buf - buffering a chained commandlets
 * @info: param structure
 * @buf:the address of the buffer value
 * @len: the address of len var value
 *
 * Return: to return bytes read along
 */
ssize_t _input_buf(info_t *info, char **buf, size_t *len)
{
	ssize_t r = 0;
	size_t len_p = 0;

	if (!*len) /* if nothing left in the buffer,we gonna fill it */
	{
		/*bfree((void **)info->cmd_buf);*/
		free(*buf);
		*buf = NULL;
		signal(SIGINT, _sigint_Handler);
#if USE_GETLINE
		r = getline(buf, &len_p, stdin);
#else
		r = _get_line(info, buf, &len_p);
#endif
		if (r > 0)
		{
			if ((*buf)[r - 1] == '\n')
			{
				(*buf)[r - 1] = '\0'; /* removing trailing newline */
				r--;
			}
			info->linecount_flag = 1;
			_remove_comments(*buf);
			_build_history_list(info, *buf, info->histcount++);
			/* if (_strchr(*buf, ';')) is this a command chain? */
			{
				*len = r;
				info->cmd_buf = buf;
			}
		}
	}
	return (r);
}

/**
 * _get_input - geting a line minus the new line
 * @info: par structure
 *
 * Return: bytes read
 */
ssize_t _get_input(info_t *info)
{
	static char *buf; /* the ';' command chain buffer */
	static size_t i, j, len;
	ssize_t r = 0;
	char **buf_p = &(info->arg), *p;

	_put_char(BUF_FLUSH);
	r = _input_buf(info, &buf, &len);
	if (r == -1) /* EOFile */
		return (-1);
	if (len)	/* check if we have commands left in the chain buffer */
	{
		j = i; /* to initiate new iterator to current buf position */
		p = buf + i; /*to get ptr for return */

		check_chain(info, buf, &j, i, len);
		while (j < len) /*to iterate to semicolon or end */
		{
			if (is_chain(info, buf, &j))
				break;
			j++;
		}

		i = j + 1; /* to increment past nulled ';'' */
		if (i >= len) /*check if reached end of buffer? */
		{
			i = len = 0; /*to reset postn and length */
			info->cmd_buf_type = CMD_NORM;
		}

		*buf_p = p; /* to pass back ptr to current command position */
		return (_str_len(p)); /* to return length of current command */
	}

	*buf_p = buf; /* if else not a chain, pass back buffer from _get_line() */
	return (r); /* to return length of buffer from _get_line() */
}

/**
 * _read_buf - reading a buffer value
 * @info: param structure
 * @buf: buffer
 * @i: size of buffer
 *
 * Return: r a sting value
 */
ssize_t _read_buf(info_t *info, char *buf, size_t *i)
{
	ssize_t r = 0;

	if (*i)
		return (0);
	r = read(info->readfd, buf, READ_BUF_SIZE);
	if (r >= 0)
		*i = r;
	return (r);
}

/**
 * _get_line - getting the next line of input from STDINPUT
 * @info: parame structure
 * @ptr: addressing of ptr to buffer, preallocated or NULL
 * @length: size of preallocated ptr print  buffer if not NULL
 *
 * Return: s which is a str
 */
int _get_line(info_t *info, char **ptr, size_t *length)
{
	static char buf[READ_BUF_SIZE];
	static size_t i, len;
	size_t k;
	ssize_t r = 0, s = 0;
	char *p = NULL, *new_p = NULL, *c;

	p = *ptr;
	if (p && length)
		s = *length;
	if (i == len)
		i = len = 0;

	r = _read_buf(info, buf, &len);
	if (r == -1 || (r == 0 && len == 0))
		return (-1);

	c = _strchr(buf + i, '\n');
	k = c ? 1 + (unsigned int)(c - buf) : len;
	new_p = _real_loc(p, s, s ? s + k : k + 1);
	if (!new_p) /* Exist MALLOC FAILURE! */
		return (p ? free(p), -1 : -1);

	if (s)
		_strncat(new_p, buf + i, k - i);
	else
		_strncpy(new_p, buf + i, k - i + 1);

	s += k - i;
	i = k;
	p = new_p;

	if (length)
		*length = s;
	*ptr = p;
	return (s);
}

/**
 * _sigint_Handler - blocking usage of  ctrl-C
 * @sig_num: the signal number used here
 *
 * Return: void always
 */
void _sigint_Handler(__attribute__((unused))int sig_num)
{
	_puts("\n");
	_puts("$ ");
	_put_char(BUF_FLUSH);
}
