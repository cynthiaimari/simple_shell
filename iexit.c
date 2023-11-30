#include "shell.h"

/**
 **_strncpy - copying  a string value
 *@dest: the destination string to be copied along to
 *@src: the source string value to be copyied to
 *@l: the amnt of char to be copied
 *Return: the concatenated string is to be returned
 */
char *_strncpy(char *dest, char *src, int l)
{
	int i, j;
	char *s = dest;

	i = 0;
	while (src[i] != '\0' && i < l - 1)
	{
		dest[i] = src[i];
		i++;
	}
	if (i < l)
	{
		j = i;
		while (j < l)
		{
			dest[j] = '\0';
			j++;
		}
	}
	return (s);
}

/**
 **_strncat - concatenating two specific  strings
 *@dest: the first string to be concate
 *@src: the second string to be conate
 *@f: the amount of bytes to be maximally used
 *Return: the concatenated string
 */
char *_strncat(char *dest, char *src, int f)
{
	int i, k;
	char *s = dest;

	i = 0;
	k = 0;
	while (dest[i] != '\0')
		i++;
	while (src[k] != '\0' && k < f)
	{
		dest[i] = src[k];
		++i;
		++k;
	}
	if (k < f)
		dest[i] = '\0';
	return (s);
}

/**
 **_strchr - locating a character in a string
 *@v: the string to be parsed in a string
 *@d: the character to look for in a string
 *Return: (v) a pointer to a memo area v
 */
char *_strchr(char *v, char d)
{
	do {
		if (*v == d)
			return (v);
	} while (*v++ != '\0');

	return (NULL);
}
