/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   command_center.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dwillard <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/15 16:41:27 by dwillard          #+#    #+#             */
/*   Updated: 2021/12/17 21:25:44 by dwillard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

static void	empty_fd_arr(void)
{
	int	temp;

	temp = 0;
	while (g_info.filed[temp])
	{
		if (temp == 32)
			break ;
		close(g_info.filed[temp]);
		temp++;
	}
	ft_bzero(g_info.filed, 32 * sizeof (int));
}

int	command_center(char *input, char ***envp)
{
	t_command	*commands;
	int			ret;

	commands = parse_string(input);
	g_info.commands = commands;
	if (commands)
	{
		ret = pipex(commands);
		if (ret == 1)
			g_info.last_prcs = 1;
		else if (ret)
			g_info.last_prcs = 127;
		get_exit(commands);
		free_command(commands);
		dup2(g_info.std_fd[0], STDIN_FILENO);
		dup2(g_info.std_fd[1], STDOUT_FILENO);
		empty_fd_arr();
	}
	*envp = g_info.env;
	errno = 0;
	g_info.error = 0;
	if (!access(g_info.minidir, F_OK))
		unlink(g_info.minidir);
	return (0);
}
