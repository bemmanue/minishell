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

#include <minishell.h>

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

static int	input(char *str, char ***doc, int fd)
{
	int	check;

	if (fd != STD_VAL && fd != HEREDOC)
		close(fd);
	if (*doc)
		free_arr(doc);
	if (str[1] != '<')
	{
		if (access(&str[1], F_OK))
			return (NO_FILE);
		if (access (&str[1], R_OK))
			return (NO_READ);
		check = open(&str[1], O_RDONLY);
		if (check < 0)
			check = OPN_ERR;
	}
	else
		check = here_doc(str, doc);
	return (check);
}

static int	output(char *str, int fd)
{
	int	check;

	if (fd != STD_VAL)
		close(fd);
	if (access(&str[1], F_OK))
		return (NO_FILE);
	if (access (&str[1], W_OK))
		return (NO_WRIT);
	if (str[1] != '>')
		check = open(&str[1], O_CREAT | O_WRONLY | O_TRUNC, 0622);
	else
		check = open(&str[1], O_CREAT | O_WRONLY | O_APPEND, 0622);
	if (check < 0)
		check = OPN_ERR;
	return (check);
}

int	*redirect(char **red_arr, int fd_pair[2], char ***document)
{
	int	counter;

	if (*document)
		free_arr(document);
	counter = 0;
	fd_pair[0] = STD_VAL;
	fd_pair[1] = STD_VAL;
	while (red_arr[counter])
	{
		if (red_arr[counter][0] == '<')
			fd_pair[0] = input(red_arr[counter], document, fd_pair[0]);
		else if (red_arr[counter][0] == '>')
			fd_pair[1] = output(red_arr[counter], fd_pair[1]);
		if (fd_pair[0] < 0 || fd_pair[1] < 0)
			return (free_arr(document));
		counter++;
	}
	return (fd_pair);
}
