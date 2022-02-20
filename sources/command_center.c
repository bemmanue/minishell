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

void	free_comm(t_command **lst)
{
	t_command	*temp1;
	t_command	*temp2;

	temp1 = *lst;
	while (temp1)
	{
		temp2 = temp1->next;
		if (temp1->argv)
			free_arr(&(temp1->argv));
		if (temp1->rdrct)
			free_arr(&(temp1->rdrct));
		free(temp1);
		temp1 = temp2;
	}
}

int	command_center(char *input, char ***envp)
{
	t_command	*commands;

	commands = parse_string(input);
	if (commands)
	{
		if (pipex(commands))
			g_info.last_prcs = 127;
		free_comm(&commands);
		dup2(g_info.std_fd[0], STDIN_FILENO);
		dup2(g_info.std_fd[1], STDOUT_FILENO);
	}
	*envp = g_info.env;
	errno = 0;
	g_info.error = 0;
	if (!access(g_info.minidir, F_OK))
		unlink(g_info.minidir);
	return (0);
}
