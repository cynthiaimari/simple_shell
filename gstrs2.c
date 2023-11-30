#include "shell.h"

/**
 * _str_cpy - coping a str
 * @dest: the dest.
 * @src: the src
 *
 * Return: ptr to destn.
 */
char *_str_cpy(char *dest, char *src)
{
	int i = 0;

	if (dest == src || src == 0)
		return (dest);
	while (src[i])
	{
		dest[i] = src[i];
		i++;
	}
	dest[i] = 0;
	return (dest);
}

/**
 * _str_dup - dups a str
 * @str: the str to dup
 *
 * Return: ptr to the dupl'd str
 */
char *_str_dup(const char *str)
{
	int length = 0;
	char *ret;

	if (str == NULL)
		return (NULL);
	while (*str++)
		length++;
	ret = malloc(sizeof(char) * (length + 1));
	if (!ret)
		return (NULL);
	for (length++; length--;)
		ret[length] = *--str;
	return (ret);
}

/**
 *_puts - printing an in-put string
 *@str: the str. to be printed
 *
 * Return: Nothing always
 */
void _puts(char *str)
{
	int i = 0;

	if (!str)
		return;
	while (str[i] != '\0')
	{
		_put_char(str[i]);
		++i;
	}
}

/**
 * _put_char - writing the char d to stdout
 * @d: The char. to print
 *
 * Return: On success 1.
 * On error, -1 is returned, and errno is set appropriately.
 */
int _put_char(char d)
{
	static int i;
	static char buf[WRITE_BUF_SIZE];

	if (d == BUF_FLUSH || i >= WRITE_BUF_SIZE)
	{
		write(1, buf, i);
		i = 0;
	}
	if (d != BUF_FLUSH)
		buf[++i] = d;
	return (1);
}
