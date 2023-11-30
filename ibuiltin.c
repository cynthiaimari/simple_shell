#include "shell.h"

/**
 * _myend - exits the interactive shell
 * @info: Structure containing potential argts. Used to maintain
 *          constant function prototype.
 *  Return: exiting with a given exit status
 *         (0) if info.argv[0] != "exit"
 */
int _myend(info_t *info)
{
	int exitcheck;

	if (info->argv[1])  /* If there is an exit argt */
	{
		exitcheck = _err_atoi(info->argv[1]);
		if (exitcheck == -1)
		{
			info->status = 2;
			_print_error(info, "Illegal number: ");
			_iputs(info->argv[1]);
			_iputchar('\n');
			return (1);
		}
		info->err_num = _err_atoi(info->argv[1]);
		return (-2);
	}
	info->err_num = -1;
	return (-2);
}

/**
 * _mycf - changing the current directory of processes
 * @info: Struct to contain pot. arguments. Used to maintain
 *          constant function prototype.
 *  Return: 0 all the time
 */
int _mycf(info_t *info)
{
	char *s, *dir, buffer[1024];
	int chdir_ret;

	s = getcwd(buffer, 1024);
	if (!s)
		_puts("TODO: >>getcwd failure emsg here<<\n");
	if (!info->argv[1])
	{
		dir = _gitenv(info, "HOME=");
		if (!dir)
			chdir_ret = /* TODO: what will this be? */
				chdir((dir = _gitenv(info, "PWD=")) ? dir : "/");
		else
			chdir_ret = chdir(dir);
	}
	else if (_str_cmp(info->argv[1], "-") == 0)
	{
		if (!_gitenv(info, "OLDPWD="))
		{
			_puts(s);
			_put_char('\n');
			return (1);
		}
		_puts(_gitenv(info, "OLDPWD=")), _put_char('\n');
		chdir_ret = /* TODO: what should this be? */
			chdir((dir = _gitenv(info, "OLDPWD=")) ? dir : "/");
	}
	else
		chdir_ret = chdir(info->argv[1]);
	if (chdir_ret == -1)
	{
		_print_error(info, "can't cd to ");
		_iputs(info->argv[1]), _put_char('\n');
	}
	else
	{
		_set_env(info, "OLDPWD", _gitenv(info, "PWD="));
		_set_env(info, "PWD", getcwd(buffer, 1024));
	}
	return (0);
}

/**
 * _myhell - changing the current directory of the process
 * @info: Structure containing potential arguments. Used to maintain
 *          constant function prototype.
 *  Return: Always 0
 */
int _myhell(info_t *info)
{
	char **arg_array;

	arg_array = info->argv;
	_puts("help call works. Function not yet implemented \n");
	if (0)
		_puts(*arg_array); /* temporary att n / unused as workaround */
	return (0);
}
