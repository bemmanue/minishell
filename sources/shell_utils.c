/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   shell_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dwillard <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/17 21:26:17 by dwillard          #+#    #+#             */
/*   Updated: 2021/12/17 21:26:20 by dwillard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

void	error(char *str, int err)
{
	ft_putstr_fd("minishell: ", 2);
	ft_putstr_fd(str, 2);
	ft_putstr_fd(": ", 2);
	if (!err)
		ft_putendl_fd(strerror(errno), 2);
	else
		ft_putendl_fd(strerror(err), 2);
	exit(-1);
}

int	command_len(t_command *command)
{
	t_command	*temp;
	int			count;

	temp = command;
	count = 0;
	while (temp)
	{
		count++;
		temp = temp->next;
	}
	return (count);
}
