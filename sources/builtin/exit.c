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

int	ft_exit(char **argv)
{
	uint8_t	code;

	if (argv && argv[1])
	{
		if (!ft_isnumeric(argv[1]))
		{
			ft_putstr_fd("bash: exit: ", STDERR_FILENO);
			ft_putstr_fd(argv[1], STDERR_FILENO);
			ft_putstr_fd(": ", STDERR_FILENO);
			ft_putendl_fd(NUM_ERROR, STDERR_FILENO);
			exit(255);
		}
		else if (argv[2])
		{
			ft_putstr_fd("bash: exit: ", STDERR_FILENO);
			ft_putendl_fd(ARG_ERROR, STDERR_FILENO);
			return (0);
		}
		else
		{
			code = ft_atol(argv[1]);
			exit((unsigned char)code);
		}
	}
	else
		exit(EXIT_SUCCESS);
}
