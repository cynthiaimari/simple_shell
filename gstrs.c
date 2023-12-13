#include "shell.h"

/**
 * _str_len - returning the len of a str
 * @s: the str whose len to check
 *
 * Return: int len of str
 */
int _str_len(char *s)
{
	int i = 0;

	if (!s)
		return (0);

	while (*s++)
		i++;
	return (i);
}

/**
 * _str_cmp - performing lexi comparison of two stranges.
 * @s1: the first stranges
 * @s2: the second stranges
 *
 * Return: -ve if s1 < s2, +ve if s1 > s2, zero if s1 == s2
 */
int _str_cmp(char *s1, char *s2)
{
	while (*s1 && *s2)
	{
		if (*s1 != *s2)
			return (*s1 - *s2);
		s1++;
		s2++;
	}
	if (*s1 == *s2)
		return (0);
	else
		return (*s1 < *s2 ? -1 : 1);
}

/**
 * _starts_wth - checking if needle starts with haystack
 * @haystack: strn to search
 * @needle: the substring to find
 *
 * Return: addr of nxt charactr of haystack or NULL
 */
char *_starts_wth(const char *haystack, const char *needle)
{
	while (*needle)
		if (*needle++ != *haystack++)
			return (NULL);
	return ((char *)haystack);
}

/**
 * _str_cat - concatenating 2 str.s
 * @dest: the destn buffer
 * @src: the src buffer
 *
 * Return: ptr to dest. buffer
 */
char *_str_cat(char *dest, char *src)
{
	char *ret = dest;

	while (*dest)
		dest++;
	while (*src)
		*dest++ = *src++;
	*dest = *src;
	return (ret);
}
