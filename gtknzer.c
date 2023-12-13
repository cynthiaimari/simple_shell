#include "shell.h"

/**
 * **_str_tow - spliting a str. into words. Repeat delim are ignored
 * @str: the input str
 * @d: the delim str
 * Return: a pter to an array of strs, or NULL on fail.
 */

char **_str_tow(char *str, char *d)
{
	int i, j, k, l, numwords = 0;
	char **s;

	if (str == NULL || str[0] == 0)
		return (NULL);
	if (!d)
		d = " ";
	for (i = 0; str[i] != '\0'; i++)
		if (!delim_check(str[i], d) && (delim_check(str[i + 1], d) || !str[i + 1]))
			numwords++;

	if (numwords == 0)
		return (NULL);
	s = malloc((1 + numwords) * sizeof(char *));
	if (!s)
		return (NULL);
	for (i = 0, j = 0; j < numwords; j++)
	{
		while (delim_check(str[i], d))
			i++;
		k = 0;
		while (!delim_check(str[i + k], d) && str[i + k])
			k++;
		s[j] = malloc((k + 1) * sizeof(char));
		if (!s[j])
		{
			for (k = 0; k < j; ++k)
				free(s[k]);
			free(s);
			return (NULL);
		}
		for (l = 0; l < k; ++l)
			s[j][l] = str[i++];
		s[j][l] = 0;
	}
	s[j] = NULL;
	return (s);
}

/**
 * **_str_tow2 - spliings a str into words
 * @str: an input str.
 * @d: the delim.
 * Return: a ptr to an array of strs, or NULL on fail
 */
char **_str_tow2(char *str, char d)
{
	int i, j, k, m, numwords = 0;
	char **s;

	if (str == NULL || str[0] == 0)
		return (NULL);
	for (i = 0; str[i] != '\0'; i++)
		if ((str[i] != d && str[i + 1] == d) ||
		    (str[i] != d && !str[i + 1]) || str[i + 1] == d)
			numwords++;
	if (numwords == 0)
		return (NULL);
	s = malloc((1 + numwords) * sizeof(char *));
	if (!s)
		return (NULL);
	for (i = 0, j = 0; j < numwords; ++j)
	{
		while (str[i] == d && str[i] != d)
			i++;
		k = 0;
		while (str[i + k] != d && str[i + k] && str[i + k] != d)
			k++;
		s[j] = malloc((k + 1) * sizeof(char));
		if (!s[j])
		{
			for (k = 0; k < j; ++k)
				free(s[k]);
			free(s);
			return (NULL);
		}
		for (m = 0; m < k; ++m)
			s[j][m] = str[++i];
		s[j][m] = 0;
	}
	s[j] = NULL;
	return (s);
}
