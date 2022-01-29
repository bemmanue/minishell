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

t_command	*parse(char *str)
{
	t_command	*ret;

	ret = malloc(sizeof (t_command *));
	ret->name = ft_strdup(str);
	ret->argv = malloc(sizeof (char *) * 2);
	ret->argv[0] = ft_strdup("");
	ret->argv[1] = NULL;
	ret->redirects = malloc(sizeof (char *) * 2);
	ret->redirects[0] = ft_strdup("");
	ret->redirects[1] = NULL;
	ret->next = NULL;
	return (ret);
}

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
		if (temp1->redirects)
			free_arr(&temp1->redirects);
		free(temp1);
		temp1 = temp2;
	}
}

int	command_center(char **envp, char *input)
{
	t_command	*commands;

//	commands = parse_string(envp, input);
	(void)input;
	(void)envp;
	commands = parse(input);
	if (pipex(commands))
		g_info.last_prcs = 127;
	free_comm(&commands);
	g_info.error = 0;
	errno = 0;
	dup2(g_info.std_fd[0], STDIN_FILENO);
	dup2(g_info.std_fd[1], STDOUT_FILENO);
	return (0);
}
