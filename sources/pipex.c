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

int	pipex(t_command **commands)
{
	int	counter;
	int	status;

	counter = 0;
	while (commands[counter])
		counter++;
	if (fork())
		waitpid(0, &status, 0);
	else
	{
		execve(commands[0]->command, NULL, NULL);
		write(2, "Error: exec\n", 12);
		exit(1);
	}
	return (0);
}
