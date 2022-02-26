/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bemmanue <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/15 16:00:00 by bemmanue          #+#    #+#             */
/*   Updated: 2022/02/15 16:00:00 by bemmanue         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <builtin.h>

int	ft_isnumeric(char *str)
{
	int	i;

	i = 0;
	if (ft_strchr("-+", *str))
		str++;
	while (str[i])
	{
		if (!ft_isdigit(str[i]))
			return (0);
		i++;
	}
	if (i > 19 && ft_atoul(str) > 9223372036854775807)
		return (0);
	return (1);
}

int	exit_success()
{
	if (!g_info.commands->next)
	{
		ft_putendl_fd("exit", STDOUT_FILENO);
		exit(EXIT_SUCCESS);
	}
	else
		return (0);
}

int	exit_num(char *argv)
{
	u_int64_t	code;

	code = ft_atoul(argv);
	if (!g_info.commands->next)
	{
		ft_putendl_fd("exit", STDOUT_FILENO);
		exit((unsigned char) code);
	}
	else
		return ((unsigned char) code);
}

int	arg_error()
{
	if (!g_info.commands->next)
		ft_putendl_fd("exit", STDOUT_FILENO);
	ft_putstr_fd("bash: exit: ", STDERR_FILENO);
	ft_putendl_fd(ARG_ERROR, STDERR_FILENO);
	return (1);
}

int	num_error(char *argv)
{
	if (!g_info.commands->next)
		ft_putendl_fd("exit", STDOUT_FILENO);
	ft_putstr_fd("bash: exit: ", STDERR_FILENO);
	ft_putstr_fd(argv, STDERR_FILENO);
	ft_putstr_fd(": ", STDERR_FILENO);
	ft_putendl_fd(NUM_ERROR, STDERR_FILENO);
	if (!g_info.commands->next)
		exit(255);
	return (255);
}

int	ft_exit(char **argv)
{
	if (argv && argv[1])
	{
		if (!ft_isnumeric(argv[1]))
			return (num_error(argv[1]));
		else if (argv[2])
			return (arg_error());
		else
			return (exit_num(argv[1]));
	}
	return (exit_success());
}
