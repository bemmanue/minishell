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
	if (str)
	{
		ft_putstr_fd(str, 2);
		ft_putstr_fd(": ", 2);
	}
	if (!err)
	{
		ft_putendl_fd(strerror(errno), 2);
		err = g_info.last_prcs;
	}
	else
		ft_putendl_fd("command not found", 2);
	exit(err);
}

void	cancel_cmd(int signo)
{
	(void)signo;
	write(1, "\n", 1);
}

void	fill_fd(int *fd_arr, int count)
{
	int	temp;

	temp = 0;
	while (g_info.filed[temp] && temp < 32)
		temp++;
	while (count-- > 0)
	{
		if (temp == 32)
			break ;
		g_info.filed[temp] = *fd_arr;
		temp++;
		fd_arr++;
	}
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

char	*ft_getenv(char **envp, char *name)
{
	char	*variable;
	int		len;
	int		index;

	variable = ft_strjoin(name, "=");
	if (!variable)
		return (NULL);
	len = (int)ft_strlen(variable);
	index = 0;
	while (envp && envp[index])
	{
		if (!ft_strncmp(envp[index], variable, len))
		{
			free(variable);
			return (envp[index] + len);
		}
		index++;
	}
	free(variable);
	return (NULL);
}
