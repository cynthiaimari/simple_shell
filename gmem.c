#include "shell.h"

/**
 * _free_it - freeing a ptr and NULLs the address
 * @ptr: address of the ptr to free up
 *
 * Return: 1 if freed success, otherwise 0.
 */
int _free_it(void **ptr)
{
	if (ptr && *ptr)
	{
		free(*ptr);
		*ptr = NULL;
		return (1);
	}
	return (0);
}
