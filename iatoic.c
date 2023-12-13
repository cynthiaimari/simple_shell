#include "shell.h"

/**
 * interact - this returns true if shell is in interactive type
 * @linfo: struct address
 *
 * Return: returns 1 if interactive mode, 0 otherwise
 */
int interact(info_t *linfo)
{
	return (isatty(STDIN_FILENO) && linfo->readfd <= 2);
}

/**
 * delim_check - this checks if character is a delimeter string
 * @c: the char to check
 * @deli: the delimeter string
 * Return: 1 if true, 0 if false
 */
int delim_check(char c, char *deli)
{
	while (*deli)
		if (*deli++ == c)
			return (1);
	return (0);
}

/**
 *alpha - checking for alphabs character
 *@c: The character to input
 *Return: Retn 1 if c is alphab, 0 otherwise
 */

int alpha(int c)
{
	if ((c >= 'a' && c <= 'z') || (c >= 'A' && c <= 'Z'))
		return (1);
	else
		return (0);
}

/**
 *strni - converts a string to an integer
 *@s: the string to be converted
 *Return: 0 if no numbers in string, converted number otherwise
 */

int strni(char *s)
{
	int i, sign = 1, flag = 0, output;
	unsigned int result = 0;

	for (i = 0;  s[i] != '\0' && flag != 2; i++)
	{
		if (s[i] == '-')
			sign *= -1;

		if (s[i] >= '0' && s[i] <= '9')
		{
			flag = 1;
			result *= 10;
			result += (s[i] - '0');
		}
		else if (flag == 1)
			flag = 2;
	}

	if (sign == -1)
		output = -result;
	else
		output = result;

	return (output);
}
