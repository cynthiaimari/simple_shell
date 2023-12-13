#include "shell.h"

/**
 * _clearinfo - initializing info_t structure
 * @info: structure address item
 */
void _clearinfo(info_t *info)
{
	info->arg = NULL;
	info->argv = NULL;
	info->path = NULL;
	info->argc = 0;
}

/**
 * _setinfo - initializing info_t structure item
 * @info: structure address item
 * @av: argumentitem  vector
 */
void _setinfo(info_t *info, char **av)
{
	int i = 0;

	info->fname = av[0];
	if (info->arg)
	{
		info->argv = _str_tow(info->arg, " \t");
		if (!info->argv)
		{

			info->argv = malloc(sizeof(char *) * 2);
			if (info->argv)
			{
				info->argv[0] = _str_dup(info->arg);
				info->argv[1] = NULL;
			}
		}
		for (i = 0; info->argv && info->argv[i]; i++)
			;
		info->argc = i;

		replace_alias(info);
		replace_vars(info);
	}
}

/**
 * _freeinfo - freeing info_t structure fields and items
 * @info: structure address field
 * @all: returning true if freeing all fields
 */
void _freeinfo(info_t *info, int all)
{
	_ffree_strn(info->argv);
	info->argv = NULL;
	info->path = NULL;
	if (all)
	{
		if (!info->cmd_buf)
			free(info->arg);
		if (info->env)
			_free_list(&(info->env));
		if (info->history)
			_free_list(&(info->history));
		if (info->alias)
			_free_list(&(info->alias));
		_ffree_strn(info->environ);
			info->environ = NULL;
		_free_it((void **)info->cmd_buf);
		if (info->readfd > 2)
			close(info->readfd);
		_put_char(BUF_FLUSH);
	}
}
