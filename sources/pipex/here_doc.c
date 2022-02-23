/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   here_doc.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dwillard <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/21 15:29:50 by dwillard          #+#    #+#             */
/*   Updated: 2022/02/21 15:29:51 by dwillard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	cancel_cmd_doc(int signo)
{
	(void)signo;
	write(1, "\n", 1);
	exit(SIG_END);
}

static void	get_readstr(char **str, int fd)
{
	ft_putendl_fd(*str, fd);
	free(*str);
	set_signals();
	signal(SIGINT, cancel_cmd_doc);
	*str = readline("> ");
}

static int	here_doc(char *delimiter)
{
	char	*str;
	int		fd;
	pid_t	pid;

	dup2(g_info.std_fd[0], STDIN_FILENO);
	dup2(g_info.std_fd[1], STDOUT_FILENO);
	pid = fork();
	if (pid > 0)
		return (pid);
	fd = open(g_info.minidir, O_CREAT | O_WRONLY | O_TRUNC, 0622);
	delimiter += 2;
	set_signals();
	signal(SIGINT, cancel_cmd);
	str = readline("> ");
	while (str && ft_strncmp(str, delimiter, ft_strlen(delimiter)))
		get_readstr(&str, fd);
	if (str)
		free(str);
	close(fd);
	exit(0);
}

int	control(char *delim)
{
	pid_t	pid;
	int		status;

	pid = here_doc(delim);
	waitpid(pid, &status, 0);
	if (WEXITSTATUS(status) == SIG_END)
	{
		g_info.last_prcs = SIG_END;
		return (SIG_END);
	}
	return (HEREDOC);
}
