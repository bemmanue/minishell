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

static int	here_doc(char *delimiter)
{
	char	*str;
	int		fd;

	dup2(g_info.std_fd[0], STDIN_FILENO);
	dup2(g_info.std_fd[1], STDOUT_FILENO);
	fd = open(g_info.minidir, O_CREAT | O_WRONLY | O_TRUNC, 0622);
	delimiter += 2;
	str = readline("> ");
	while (str && ft_strncmp(str, delimiter, ft_strlen(delimiter)))
	{
		ft_putendl_fd(str, fd);
		free(str);
		str = readline("> ");
	}
	if (str)
		free(str);
	close(fd);
	return (HEREDOC);
}

static int	input(char *str, int fd)
{
	int	check;

	check = 0;
	if (fd != STD_VAL)
		close(fd);
	if (!access(g_info.minidir, F_OK))
		unlink(g_info.minidir);
	if (str[1] != '<')
	{
		if (access(&str[1], F_OK))
			check = NO_FILE;
		if (access (&str[1], R_OK) && !check)
			check = NO_READ;
		if (check)
			g_info.error = check;
		if (!check)
			check = open(&str[1], O_RDONLY);
		if (check < 0)
			check = OPN_ERR;
	}
	else
		check = here_doc(str);
	if (check < 0)
		g_info.error = check;
	return (check);
}

static int	output(char *str, int fd)
{
	int	check;

	check = 0;
	if (fd != STD_VAL)
		close(fd);
	if (!access(&str[1], F_OK) && access(&str[1], W_OK))
		check = NO_WRIT;
	if (check)
	{
		g_info.error = check;
		return (check);
	}
	if (str[1] != '>')
		check = open(&str[1], O_CREAT | O_WRONLY | O_TRUNC, 0622);
	else
		check = open(&str[2], O_CREAT | O_WRONLY | O_APPEND, 0622);
	if (check < 0)
	{
		check = OPN_ERR;
		g_info.error = check;
	}
	return (check);
}

int	*redirect(char **red_arr, int fd_pair[2])
{
	int		counter;

	fd_pair[0] = STD_VAL;
	fd_pair[1] = STD_VAL;
	if (!red_arr)
		return (fd_pair);
	counter = 0;
	while (red_arr[counter])
	{
		if (red_arr[counter][0] == '<')
			fd_pair[0] = input(red_arr[counter], fd_pair[0]);
		else if (red_arr[counter][0] == '>')
			fd_pair[1] = output(red_arr[counter], fd_pair[1]);
		if (fd_pair[0] < 0 || fd_pair[1] < 0)
			return (NULL);
		counter++;
	}
	return (fd_pair);
}
