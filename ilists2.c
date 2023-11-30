#include "shell.h"

/**
 * _list_len - determining the len of linked list
 * @h: ptr to first node
 *
 * Return: size of the final list
 */
size_t _list_len(const list_t *h)
{
	size_t i = 0;

	while (h)
	{
		h = h->next;
		i++;
	}
	return (i);
}

/**
 * _list_to_strings - returned an array of strings of the list->str
 * @head: ptr to a first node
 *
 * Return: array of strings
 */
char **_list_to_strings(list_t *head)
{
	list_t *node = head;
	size_t i = _list_len(head), j;
	char **strs;
	char *str;

	if (!head || !i)
		return (NULL);
	strs = malloc(sizeof(char *) * (i + 1));
	if (!strs)
		return (NULL);
	for (i = 0; node; node = node->next, i++)
	{
		str = malloc(_str_len(node->str) + 1);
		if (!str)
		{
			for (j = 0; j < i; j++)
				free(strs[j]);
			free(strs);
			return (NULL);
		}

		str = _str_cpy(str, node->str);
		strs[i] = str;
	}
	strs[i] = NULL;
	return (strs);
}


/**
 * _print_list - prints all elements of a list_t linked list
 * @m: ptr to first node
 *
 * Return: size of list
 */
size_t _print_list(const list_t *m)
{
	size_t z = 0;

	while (m)
	{
		_puts(_convert_number(m->num, 10, 0));
		_put_char(':');
		_put_char(' ');
		_puts(m->str ? m->str : "(nil)");
		_puts("\n");
		m = m->next;
		++z;
	}
	return (z);
}

/**
 * _node_starts_with - returning a node whose string starts with prefix list
 * @node: ptr to list head
 * @prefix: string to match item
 * @d: the next char after prefix to match
 *
 * Return: match node or null
 */
list_t *_node_starts_with(list_t *node, char *prefix, char d)
{
	char *p = NULL;

	while (node)
	{
		p = _starts_wth(node->str, prefix);
		if (p && ((d == -1) || (*p == d)))
			return (node);
		node = node->next;
	}
	return (NULL);
}

/**
 * _get_node_index - getting the index of a node
 * @head: ptr to list head
 * @node: ptr to the node
 *
 * Return: index of node or -1
 */
ssize_t _get_node_index(list_t *head, list_t *node)
{
	size_t k = 0;

	while (head)
	{
		if (head == node)
			return (k);
		head = head->next;
		++k;
	}
	return (-1);
}
