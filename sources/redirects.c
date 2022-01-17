/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirects.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dwillard <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/17 18:28:36 by dwillard          #+#    #+#             */
/*   Updated: 2022/01/17 19:22:31 by dwillard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

static int	input(char *str)
{
	if (str[1] != '<')
		;
	else
		here_doc();
	return (0);
}

static int	output(char *str)
{
	return (0);
}

int	*redirect(char **red_arr)
{
	int	counter;
	int	*fd_pair;

	counter = 0;
	fd_pair = malloc(sizeof(int) * 2);
	fd_pair[0] = STDIN_FILENO;
	fd_pair[1] = STDOUT_FILENO;
	while (red_arr[counter])
	{
		if (red_arr[counter][0] == '<')
			fd_pair[0] = input(red_arr[counter]);
		else if (red_arr[counter][0] == '>')
			fd_pair[1] = output(red_arr[counter]);
		counter++;
	}
	return (fd_pair);
}
