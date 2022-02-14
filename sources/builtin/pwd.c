/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dwillard <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/14 20:57:17 by dwillard          #+#    #+#             */
/*   Updated: 2022/01/14 20:57:18 by dwillard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <builtin.h>

int	ft_pwd(char **argv)
{
	char	*temp;

	temp = getcwd(NULL, 0);
	if (!temp)
		return (-1);
	if (argv && argv[1])
	{
	    ft_putstr_fd("minishell: pwd: ", STDERR_FILENO);
	    ft_putendl_fd(ARG_ERROR, STDERR_FILENO);
	    return (-1);
	}
	ft_putendl_fd(temp, 1);
	free(temp);
	return (0);
}