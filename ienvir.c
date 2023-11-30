#include "shell.h"

/**
 * _mienv - printing current envirnt
 * @info: Struct contains potential argts. Used to maintain
 *          constant funct prototype program.
 * Return: Always 0 as usual
 */
int _mienv(info_t *info)
{
	_print_list_str(info->env);
	return (0);
}

/**
 * _gitenv - geting the value of an environ variable
 * @info: Struct contains potential arguments. Used to maintain
 * @name: env var name
 *
 * Return: the value in
 */
char *_gitenv(info_t *info, const char *name)
{
	list_t *node = info->env;
	char *p;

	while (node)
	{
		p = _starts_wth(node->str, name);
		if (p && *p)
			return (p);
		node = node->next;
	}
	return (NULL);
}

/**
 * _misetenv - Initializing  new envirnt variable,
 *             or modifying an existing one itm
 * @info: Structure contains essentila arguments. Used to maintain
 *        constant function prototype program.
 *  Return: Always 0 as usual
 */
int _misetenv(info_t *info)
{
	if (info->argc != 3)
	{
		_iputs("Incorrect number of arguements\n");
		return (1);
	}
	if (_set_env(info, info->argv[1], info->argv[2]))
		return (0);
	return (1);
}

/**
 * _miunsetenv - Removes an environt variable item
 * @info: Structure contains potential arguments. Used to maintain
 *        constant functn prototype program.
 *  Return: Always 0
 */
int _miunsetenv(info_t *info)
{
	int i;

	if (info->argc == 1)
	{
		_iputs("Too few arguements.\n");
		return (1);
	}
	for (i = 1; i <= info->argc; i++)
		_unset_env(info, info->argv[i]);

	return (0);
}

/**
 * pop_env_list - populating a env linked list
 * @info: Struct contains potential arguments. Used to maintain
 *          const funct prototype.
 * Return: 0 Always return
 */
int pop_env_list(info_t *info)
{
	list_t *node = NULL;
	size_t i;

	for (i = 0; environ[i]; i++)
		_add_node_end(&node, environ[i], 0);
	info->env = node;
	return (0);
}
