#include "shell.h"

/**
 **_mem_set - filling mem with a constant byte
 *@s: the ptr to the mem. area
 *@b: the byte to fill *s with
 *@n: the amnt of bytes to be filled up
 *Return: (s) a ptr to the mem area s
 */
char *_mem_set(char *s, char b, unsigned int n)
{
	unsigned int z;

	for (z = 0; z < n; ++z)
		s[z] = b;
	return (s);
}

/**
 * _ffree_strn - freeing a str of strs
 * @pp: str of strs
 */
void _ffree_strn(char **pp)
{
	char **a = pp;

	if (!pp)
		return;
	while (*pp)
		free(*pp++);
	free(a);
}

/**
 * _real_loc - reallocating a block of mem.
 * @ptr: ptr to previous malloc'ated block
 * @old_size: byte size of prev. block
 * @new_size: byte size of new block
 *
 * Return: ptr to da ol'block nameen.
 */
void *_real_loc(void *ptr, unsigned int old_size, unsigned int new_size)
{
	char *l;

	if (!ptr)
		return (malloc(new_size));
	if (!new_size)
		return (free(ptr), NULL);
	if (new_size == old_size)
		return (ptr);

	l = malloc(new_size);
	if (!l)
		return (NULL);

	old_size = old_size < new_size ? old_size : new_size;
	while (old_size--)
		l[old_size] = ((char *)ptr)[old_size];
	free(ptr);
	return (l);
}
