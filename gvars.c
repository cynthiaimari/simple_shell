#include "shell.h"

/**
 * is_chain - testing if current char in buffer is a chain delim.
 * @info: the param. structure
 * @buf: the char buffer
 * @p: address of current postn in buff
 *
 * Return: 1 if chain delimeter, 0 otherwise
 */
int is_chain(info_t *info, char *buf, size_t *p)
{
	size_t j = *p;

	if (buf[j] == '|' && buf[j + 1] == '|')
	{
		buf[j] = 0;
		j++;
		info->cmd_buf_type = CMD_OR;
	}
	else if (buf[j] == '&' && buf[j + 1] == '&')
	{
		buf[j] = 0;
		j++;
		info->cmd_buf_type = CMD_AND;
	}
	else if (buf[j] == ';') /* end of this command */
	{
		buf[j] = 0; /* replace semicolon */
		info->cmd_buf_type = CMD_CHAIN;
	}
	else
		return (0);
	*p = j;
	return (1);
}

/**
 * check_chain - checking we should continue chaining based lst status
 * @info: the param. structure
 * @buf: the char buffer item
 * @p: address of current posn in buf
 * @i: starting postn in buf
 * @len: length of buff
 *
 * Return: Void
 */
void check_chain(info_t *info, char *buf, size_t *p, size_t i, size_t len)
{
	size_t j = *p;

	if (info->cmd_buf_type == CMD_AND)
	{
		if (info->status)
		{
			buf[i] = 0;
			j = len;
		}
	}
	if (info->cmd_buf_type == CMD_OR)
	{
		if (!info->status)
		{
			buf[i] = 0;
			j = len;
		}
	}

	*p = j;
}

/**
 * replace_alias - replacing an aliases in the tokenized str.
 * @info: the param. structure
 *
 * Return: 1 if replaced, 0 otherwise
 */
int replace_alias(info_t *info)
{
	int i;
	list_t *node;
	char *p;

	for (i = 0; i < 10; i++)
	{
		node = _node_starts_with(info->alias, info->argv[0], '=');
		if (!node)
			return (0);
		free(info->argv[0]);
		p = _strchr(node->str, '=');
		if (!p)
			return (0);
		p = _str_dup(p + 1);
		if (!p)
			return (0);
		info->argv[0] = p;
	}
	return (1);
}

/**
 * replace_vars - replacing vars in the tokenized str
 * @info: the param structure
 *
 * Return: 1 if replaced, 0 otherwise always
 */
int replace_vars(info_t *info)
{
	int i = 0;
	list_t *node;

	for (i = 0; info->argv[i]; i++)
	{
		if (info->argv[i][0] != '$' || !info->argv[i][1])
			continue;

		if (!_str_cmp(info->argv[i], "$?"))
		{
			replace_string(&(info->argv[i]),
				_str_dup(_convert_number(info->status, 10, 0)));
			continue;
		}
		if (!_str_cmp(info->argv[i], "$$"))
		{
			replace_string(&(info->argv[i]),
				_str_dup(_convert_number(getpid(), 10, 0)));
			continue;
		}
		node = _node_starts_with(info->env, &info->argv[i][1], '=');
		if (node)
		{
			replace_string(&(info->argv[i]),
				_str_dup(_strchr(node->str, '=') + 1));
			continue;
		}
		replace_string(&info->argv[i], _str_dup(""));

	}
	return (0);
}

/**
 * replace_string - replacing str.
 * @old: address of old str.
 * @new: new str.
 *
 * Return: 1 if replaced, 0 otherwise always
 */
int replace_string(char **old, char *new)
{
	free(*old);
	*old = new;
	return (1);
}
