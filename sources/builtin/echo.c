/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dwillard <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/20 18:34:17 by dwillard          #+#    #+#             */
/*   Updated: 2021/12/20 21:32:24 by dwillard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtin.h"

static int	ft_strlen(char *str)
{
	int	counter;

	counter = 0;
	while (str[counter])
		counter++;
	return (counter);
}

static void	ft_putstr(char *str, int flag)
{
	write(STDOUT_FILENO, str, ft_strlen(str));
	if (flag == 1)
		write(STDOUT_FILENO, " ", 1);
	if (flag == 2)
		write(STDOUT_FILENO, "\n", 1);
}

static int	ft_strncmp(const char *str1, const char *str2, int stop)
{
	while (stop-- && *str1++ == *str2++)
		;
	return (*str1 - *str2);
}

static void	ft_cycle(int flag, int index, char **argv)
{
	while (argv[index])
	{
		if (!argv[index + 1])
			ft_putstr(argv[index], flag);
		else
			ft_putstr(argv[index], 1);
		index++;
	}
}

int	echo(int argc, char **argv)
{
	if (argc < 2)
		return (write(STDOUT_FILENO, "\n", 1) - 1);
	if (argc == 2 && !ft_strncmp(argv[1], "-n", 2))
		return (0);
	if (argc > 2 && !ft_strncmp(argv[1], "-n", 3))
		ft_cycle(0, 2, argv);
	else
		ft_cycle(2, 1, argv);
	return (0);
}
