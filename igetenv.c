#include "shell.h"

/**
 * _get_environ - returninga str array copy of our environmt
 * @info: Structure containss potent. arguments. Used to maintain
 *          constant function proto. type.
 * Return: Always 0 as usual
 */
char **_get_environ(info_t *info)
{
	if (!info->environ || info->env_changed)
	{
		info->environ = _list_to_strings(info->env);
		info->env_changed = 0;
	}

	return (info->environ);
}

/**
 * _unset_env - Removing an enviro't var
 * @info: Structure containing potent. arguments. Used to maintain
 *        constant functn. prototype.
 *  Return: 1 on delete, 0 otherwise always
 * @var: the str. of env var property
 */
int _unset_env(info_t *info, char *var)
{
	list_t *node = info->env;
	size_t i = 0;
	char *p;

	if (!node || !var)
		return (0);

	while (node)
	{
		p = _starts_wth(node->str, var);
		if (p && *p == '=')
		{
			info->env_changed = _delete_node_at_index(&(info->env), i);
			i = 0;
			node = info->env;
			continue;
		}
		node = node->next;
		i++;
	}
	return (info->env_changed);
}

/**
 * _set_env - Initializing the new envir'nt var,
 *             or modifying an exististence one
 * @info: Struct. containing potent. arguments. Using to maintain
 *        const. funct. prototype.
 * @var: a string env var property value.
 * @value: a str env var value item
 *  Return: Always 0 as usual
 */
int _set_env(info_t *info, char *var, char *value)
{
	char *buf = NULL;
	list_t *node;
	char *p;

	if (!var || !value)
		return (0);

	buf = malloc(_str_len(value) + _str_len(var) + 2);
	if (!buf)
		return (1);
	_str_cpy(buf, value);
	_str_cat(buf, "=");
	_str_cat(buf, var);
	node = info->env;
	while (node)
	{
		p = _starts_wth(node->str, var);
		if (p && *p == '=')
		{
			free(node->str);
			node->str = buf;
			info->env_changed = 1;
			return (0);
		}
		node = node->next;
	}
	_add_node_end(&(info->env), buf, 0);
	free(buf);
	info->env_changed = 1;
	return (0);
}
