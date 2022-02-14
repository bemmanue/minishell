#include <builtin.h>

int	ft_exit(char **argv)
{
	if (argv[1])
	{
		ft_putstr_fd("minishell: exit: ", STDERR_FILENO);
		ft_putendl_fd(ARG_ERROR, STDERR_FILENO);
		return (-1);
	}
	exit(EXIT_SUCCESS);
}
