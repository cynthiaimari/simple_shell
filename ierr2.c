#include "shell.h"

/**
 * _err_atoi - converting a str. to an int.
 * @s: the str. to be converted
 * Return: 0 if no numbers in str., converted number otherwise
 *       -1 on error
 */
int _err_atoi(char *s)
{
	int i = 0;
	unsigned long int result = 0;

	if (*s == '+')
		++s;
	for (i = 0;  s[i] != '\0'; i++)
	{
		if (s[i] >= '0' && s[i] <= '9')
		{
			result *= 10;
			result += (s[i] - '0');
			if (result > INT_MAX)
				return (-1);
		}
		else
			return (-1);
	}
	return (result);
}

/**
 * _print_error - printing an err msg
 * @info: the para & rtn info structure
 * @estr: stn containing specified err. type
 * Return: 0 if no numbers in str, converted number otherwise
 *        -1 on error
 */
void _print_error(info_t *info, char *estr)
{
	_iputs(info->fname);
	_iputs(": ");
	_print_d(info->line_count, STDERR_FILENO);
	_iputs(": ");
	_iputs(info->argv[0]);
	_iputs(": ");
	_iputs(estr);
}

/**
 * _print_d - fn printing a decimal (int) no. (base 10)
 * @input: the input
 * @fd: the file-descriptor to write to
 *
 * Return: no. of chars printed
 */
int _print_d(int input, int fd)
{
	int (*__putchar)(char) = _put_char;
	int i, count = 0;
	unsigned int _abs_, current;

	if (fd == STDERR_FILENO)
		__putchar = _iputchar;
	if (input < 0)
	{
		_abs_ = -input;
		__putchar('-');
		count++;
	}
	else
		_abs_ = input;
	current = _abs_;
	for (i = 1000000000; i > 1; i /= 10)
	{
		if (_abs_ / i)
		{
			__putchar('0' + current / i);
			count++;
		}
		current %= i;
	}
	__putchar('0' + current);
	count++;

	return (count);
}

/**
 * _convert_number - converting fn, a clone of itoa
 * @num: no.
 * @base: base
 * @flags: args flags
 *
 * Return: str
 */
char *_convert_number(long int num, int base, int flags)
{
	static char *array;
	static char buffer[50];
	char sign = 0;
	char *ptr;
	unsigned long n = num;

	if (!(flags & CONVERT_UNSIGNED) && num < 0)
	{
		n = -num;
		sign = '-';

	}
	array = flags & CONVERT_LOWERCASE ? "0123456789abcdef" : "0123456789ABCDEF";
	ptr = &buffer[49];
	*ptr = '\0';

	do	{
		*--ptr = array[n % base];
		n /= base;
	} while (n != 0);

	if (sign)
		*--ptr = sign;
	return (ptr);
}

/**
 * _remove_comments - fn replacing first instance of '#' with '\0'
 * @buf: address of the str to modify
 *
 * Return: Always 0;
 */
void _remove_comments(char *buf)
{
	int i;

	for (i = 0; buf[i] != '\0'; i++)
		if (buf[i] == '#' && (!i || buf[i - 1] == ' '))
		{
			buf[i] = '\0';
			break;
		}
}
