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

#define NO_FILE -1
#define NO_READ -2
#define MEM_ERR -3
#define HEREDOC -4

static int	here_doc(char *delimiter, char ***doc)
{
	char	*str;
	char	**dup_doc;
	int		index;

	index = 0;
	dup_doc = ft_calloc(256 + 1, sizeof (char *));
	*doc = dup_doc;
	if (!dup_doc)
		return (MEM_ERR);
	delimiter += 2;
	str = readline("> ");
	while (str && ft_strncmp(str, delimiter, ft_strlen(delimiter)))
	{
		dup_doc[index] = ft_strdup(str);
		free(str);
		str = readline("> ");
		if (!dup_doc[index])
		{
			free_arr(doc);
			break ;
		}
	}
	if (str)
		free(str);
	return (HEREDOC);
}

static int	input(char *str, char ***doc)
{
	int	check;

	check = 0;
	if (str[1] != '<')
	{
		if (access(&str[1], F_OK))
			return (NO_FILE);
		if (access (&str[1], R_OK))
			return (NO_READ);
	}
	else
		check = here_doc(str, doc);
	return (check);
}

static int	output(char *str)
{
	return (0);
}

int	*redirect(char **red_arr, char ***document)
{
	int	counter;
	int	*fd_pair;

	if (*document)
		free_arr(document);
	counter = 0;
	fd_pair = malloc(sizeof(int) * 2);
	fd_pair[0] = STDIN_FILENO;
	fd_pair[1] = STDOUT_FILENO;
	while (red_arr[counter])
	{
		if (red_arr[counter][0] == '<')
			fd_pair[0] = input(red_arr[counter], document);
		else if (red_arr[counter][0] == '>')
			fd_pair[1] = output(red_arr[counter]);
		counter++;
	}
	return (fd_pair);
}
