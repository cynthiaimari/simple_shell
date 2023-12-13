#include "shell.h"

/**
 * _myhistory - hist displaying the hist list, one command by line, preceded
 *              with line numbers, starting at 0 onwards.
 * @info: Struct containing potent. arg.s. Used to maintain
 *        const. fn proto.type.
 *  Return: Always 0
 */
int _myhistory(info_t *info)
{
	_print_list(info->history);
	return (0);
}

/**
 * unset_alias - setting alias to string
 * @info: param. struct
 * @str: the string alias
 *
 * Return: Always 0 on success, 1 on error
 */
int unset_alias(info_t *info, char *str)
{
	char *p, c;
	int ret;

	p = _strchr(str, '=');
	if (!p)
		return (1);
	c = *p;
	*p = 0;
	ret = _delete_node_at_index(&(info->alias),
		_get_node_index(info->alias, _node_starts_with(info->alias, str, -1)));
	*p = c;
	return (ret);
}

/**
 * set_alias - seting alias to string
 * @info: param. structure
 * @str: the string alias item
 *
 * Return: Always 0 on success, 1 on error
 */
int set_alias(info_t *info, char *str)
{
	char *p;

	p = _strchr(str, '=');
	if (!p)
		return (1);
	if (!*++p)
		return (unset_alias(info, str));

	unset_alias(info, str);
	return (_add_node_end(&(info->alias), str, 0) == NULL);
}

/**
 * _print_alias - printing an alias str
 * @node: the alias node item
 *
 * Return: Always 0 on success, 1 on error
 */
int _print_alias(list_t *node)
{
	char *p = NULL, *a = NULL;

	if (node)
	{
		p = _strchr(node->str, '=');
		for (a = node->str; a <= p; a++)
			_put_char(*a);
		_put_char('\'');
		_puts(p + 1);
		_puts("'\n");
		return (0);
	}
	return (1);
}

/**
 * _myalias - mimicking the alias builtin (man alias)
 * @info: Struct. containing potent. arguments. Used to maintain
 *          constant funct. prototype.
 *  Return: Always 0
 */
int _myalias(info_t *info)
{
	int i = 0;
	char *p = NULL;
	list_t *node = NULL;

	if (info->argc == 1)
	{
		node = info->alias;
		while (node)
		{
			_print_alias(node);
			node = node->next;
		}
		return (0);
	}
	for (i = 1; info->argv[i]; i++)
	{
		p = _strchr(info->argv[i], '=');
		if (p)
			set_alias(info, info->argv[i]);
		else
			_print_alias(_node_starts_with(info->alias, info->argv[i], '='));
	}

	return (0);
}
