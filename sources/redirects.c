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

static void	cancel_cmd(int signo)
{
	(void)signo;
	write(1, "\n", 1);
	exit(130);
}

static int	here_doc(char *delimiter)
{
	char	*str;
	int		fd;
	pid_t 	pid;

	dup2(g_info.std_fd[0], STDIN_FILENO);
	dup2(g_info.std_fd[1], STDOUT_FILENO);
	pid = fork();
	if (pid > 0)
		return (pid);
	fd = open(g_info.minidir, O_CREAT | O_WRONLY | O_TRUNC, 0622);
	delimiter += 2;
	str = readline("> ");
	while (str && ft_strncmp(str, delimiter, ft_strlen(delimiter)))
	{
		ft_putendl_fd(str, fd);
		free(str);
		signal(SIGINT, ft_signal_c);
		signal(SIGINT, cancel_cmd);
		str = readline("> ");
	}
	if (str)
		free(str);
	close(fd);
	exit(0);
}

static int	input(char *str, int fd)
{
	if (fd != STD_VAL)
		close(fd);
	if (!access(g_info.minidir, F_OK))
		unlink(g_info.minidir);
	if (str[1] != '<')
	{
		if (access(&str[1], F_OK))
			fd = NO_FILE;
		if (access (&str[1], R_OK) && !fd)
			fd = NO_READ;
		if (fd)
			g_info.error = fd;
		if (!fd)
			fd = open(&str[1], O_RDONLY);
		if (fd < 0)
			fd = OPN_ERR;
	}
	else
	{
		fd = here_doc(str);
		waitpid(fd, NULL, 0);
	}
	if (fd < 0)
		g_info.error = fd;
	else
		fill_fd(&fd, 1);
	return (fd);
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
	else
		fill_fd(&check, 1);
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
	fill_fd(fd_pair, 2);
	return (fd_pair);
}
