/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bemmanue <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/15 15:00:00 by bemmanue          #+#    #+#             */
/*   Updated: 2022/02/15 15:00:00 by bemmanue         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <builtin.h>

int	ft_env(char **argv, char **envp)
{
	int	i;

	if (argv && argv[1])
	{
		ft_putstr_fd("minishell: env: ", STDERR_FILENO);
		ft_putendl_fd(ARG_ERROR, STDERR_FILENO);
		return (-1);
	}
	i = 0;
	while (envp && envp[i])
	{
		ft_putendl_fd(envp[i], STDOUT_FILENO);
		i++;
	}
	return (0);
}
