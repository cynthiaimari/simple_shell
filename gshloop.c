#include "shell.h"

/**
 * hsh - this is the main shell loop
 * @info: the param. & return info struct
 * @av: the arg't vector from main()
 *
 * Return: 0 on success, 1 on error, or error codeelse
 */
int hsh(info_t *info, char **av)
{
	ssize_t r = 0;
	int builtin_ret = 0;

	while (r != -1 && builtin_ret != -2)
	{
		_clearinfo(info);
		if (interact(info))
			_puts("$ ");
		_iputchar(BUF_FLUSH);
		r = _get_input(info);
		if (r != -1)
		{
			_setinfo(info, av);
			builtin_ret = _find_builtin(info);
			if (builtin_ret == -1)
				_find_cmd(info);
		}
		else if (interact(info))
			_put_char('\n');
		_freeinfo(info, 0);
	}
	_write_history(info);
	_freeinfo(info, 1);
	if (!interact(info) && info->status)
		exit(info->status);
	if (builtin_ret == -2)
	{
		if (info->err_num == -1)
			exit(info->status);
		exit(info->err_num);
	}
	return (builtin_ret);
}

/**
 * _find_builtin - finding ofa non custom  builtin commands
 * @info: the param. & return info structure
 *
 * Return: -1 if builtin not found,
 *			0 if builtin executed successfully,
 *			1 if builtin found but not successful,
 *			-2 if builtin signals exit()
 */
int _find_builtin(info_t *info)
{
	int i, built_in_ret = -1;
	builtin_table builtintbl[] = {
		{"exit", _myend},
		{"env", _mienv},
		{"help", _myhell},
		{"history", _myhistory},
		{"setenv", _misetenv},
		{"unsetenv", _miunsetenv},
		{"cd", _mycf},
		{"alias", _myalias},
		{NULL, NULL}
	};

	for (i = 0; builtintbl[i].type; i++)
		if (_str_cmp(info->argv[0], builtintbl[i].type) == 0)
		{
			info->line_count++;
			built_in_ret = builtintbl[i].func(info);
			break;
		}
	return (built_in_ret);
}

/**
 * _find_cmd - finding a command in PATH
 * @info: the parameter & return info struct
 *
 * Return: void
 */
void _find_cmd(info_t *info)
{
	char *path = NULL;
	int i, k;

	info->path = info->argv[0];
	if (info->linecount_flag == 1)
	{
		info->line_count++;
		info->linecount_flag = 0;
	}
	for (i = 0, k = 0; info->arg[i]; i++)
		if (!delim_check(info->arg[i], " \t\n"))
			++k;
	if (!k)
		return;

	path = _find_path(info, _gitenv(info, "PATH="), info->argv[0]);
	if (path)
	{
		info->path = path;
		_fork_cmd(info);
	}
	else
	{
		if ((interact(info) || _gitenv(info, "PATH=")
			|| info->argv[0][0] == '/') && _is_cmd(info, info->argv[0]))
			_fork_cmd(info);
		else if (*(info->arg) != '\n')
		{
			info->status = 127;
			_print_error(info, "not found\n");
		}
	}
}

/**
 * _fork_cmd - forking a an exec thread to run cmd
 * @info: the param. & return info structure
 *
 * Return: void
 */
void _fork_cmd(info_t *info)
{
	pid_t child_pid;

	child_pid = fork();
	if (child_pid == -1)
	{
		/* TODO: PUTTING ERROR FUNCTION HERE */
		perror("Error:");
		return;
	}
	if (child_pid == 0)
	{
		if (execve(info->path, info->argv, _get_environ(info)) == -1)
		{
			_freeinfo(info, 1);
			if (errno == EACCES)
				exit(126);
			exit(1);
		}
		/* TODO: TO PUTT ERROR FUNCTION HERE */
	}
	else
	{
		wait(&(info->status));
		if (WIFEXITED(info->status))
		{
			info->status = WEXITSTATUS(info->status);
			if (info->status == 126)
				_print_error(info, "Permission denied\n");
		}
	}
}
