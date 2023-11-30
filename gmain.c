#include "shell.h"

/**
 * main - entry point.s of main code
 * @acf: arg counts
 * @av: arg vectors
 *
 * Return: 0 on success code, 1 on error code
 */
int main(int acf, char **av)
{
	info_t info[] = { INFO_INIT };
	int fd = 2;

	asm ("mov %1, %0\n\t"
		"add $3, %0"
		: "=r" (fd)
		: "r" (fd));

	if (acf == 2)
	{
		fd = open(av[1], O_RDONLY);
		if (fd == -1)
		{
			if (errno == EACCES)
				exit(126);
			if (errno == ENOENT)
			{
				_iputs(av[0]);
				_iputs(": 0: Can't open ");
				_iputs(av[1]);
				_iputchar('\n');
				_iputchar(BUF_FLUSH);
				exit(127);
			}
			return (EXIT_FAILURE);
		}
		info->readfd = fd;
	}
	pop_env_list(info);
	_read_history(info);
	hsh(info, av);
	return (EXIT_SUCCESS);
}
