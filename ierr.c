#include "shell.h"

/**
 *_iputs - printing an input string
 * @str: the string to be printed
 *
 * Return: Nothing at all
 */
void _iputs(char *str)
{
	int i = 0;

	if (!str)
		return;
	while (str[i] != '\0')
	{
		_iputchar(str[i]);
		++i;
	}
}

/**
 * _iputchar - writing a character c to standarderr
 * @c: The character to be print
 *
 * Return: On success 1 always.
 * On error, -1 is returned, and errno is set accordingly.
 */
int _iputchar(char c)
{
	static int i;
	static char buf[WRITE_BUF_SIZE];

	if (c == BUF_FLUSH || i >= WRITE_BUF_SIZE)
	{
		write(2, buf, i);
		i = 0;
	}
	if (c != BUF_FLUSH)
		buf[i++] = c;
	return (1);
}

/**
 * _putfd - writing the character c to given fd
 * @c: The character to be print
 * @fd: The file descriptor to write to now
 *
 * Return: On success 1 always.
 * On error, -1 is returned, and errno is set accordingly.
 */
int _putfd(char c, int fd)
{
	static int i;
	static char buf[WRITE_BUF_SIZE];

	if (c == BUF_FLUSH || i >= WRITE_BUF_SIZE)
	{
		write(fd, buf, i);
		i = 0;
	}
	if (c != BUF_FLUSH)
		buf[i++] = c;
	return (1);
}

/**
 *_putsfd - printing an input string
 * @str: the string to  print now
 * @fd: the file descriptor to be written to
 *
 * Return: the number of chars put in place
 */
int _putsfd(char *str, int fd)
{
	int i = 0;

	if (!str)
		return (0);
	while (*str)
	{
		i += _putfd(*str++, fd);
	}
	return (i);
}
