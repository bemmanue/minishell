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
		free(temp1->name);
		if (temp1->argv)
			free_arr(&temp1->argv);
		if (temp1->rdrct)
			free_arr(&temp1->rdrct);
		free(temp1);
		temp1 = temp2;
	}
}

static int  set_name(t_command *commands)
{
	char    *temp;
	char	*temp1;
	int		counter;

	while (commands)
	{
		counter = 0;
		commands->name = ft_strdup(commands->argv[0]);
		temp = commands->name;
		temp1 = NULL;
		free(commands->argv[0]);
		while (temp[counter])
		{
			if (temp[counter] == '/')
				temp1 = &temp[counter + 1];
			counter++;
		}
		if (!temp1)
			commands->argv[0] = ft_strdup(temp);
		else
			commands->argv[0] = ft_strdup(temp1);
		if (!commands->name || !commands->argv[0])
			return (-1);
		commands = commands->next;
	}
	return (0);
}

int	command_center(char *input)
{
	t_command	*commands;

	commands = parse_string(input);
    if (commands && set_name(commands))
		error("minishell", errno);
	if (commands)
	{
		if (pipex(commands))
			g_info.last_prcs = 127;
		free_comm(&commands);
		dup2(g_info.std_fd[0], STDIN_FILENO);
		dup2(g_info.std_fd[1], STDOUT_FILENO);
	}
	errno = 0;
	g_info.error = 0;
	return (0);
}
