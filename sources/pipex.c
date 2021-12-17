/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dwillard <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/15 17:16:21 by dwillard          #+#    #+#             */
/*   Updated: 2021/12/15 17:16:23 by dwillard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	pipex(t_command *commands, char **envp)
{
	int		status;
	char	**argv;

	printf("%s\n", commands->name);
	argv = malloc(sizeof(char *) * 2);
	argv[0] = " ";
	argv[1] = NULL;
	if (fork())
		waitpid(0, &status, 0);
	else
	{
		status = execve(commands->name, argv, envp);
		write(2, "Error: exec\n", 12);
		exit(status);
	}
	return (0);
}
