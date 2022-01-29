/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dwillard <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/15 17:16:21 by dwillard          #+#    #+#             */
/*   Updated: 2021/12/17 21:26:14 by dwillard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

int	chk_builtin(t_command *commands)
{
	char	*name;
	int		code;
	int		argc;

	argc = 0;
	while (commands->argv[argc])
		argc++;
	code = NONBLTN;
	name = commands->name;
	if (!ft_strncmp(name, g_info.bltn[0], 5))
		code = echo(argc, commands->argv);
	if (!ft_strncmp(name, g_info.bltn[1], 3))
		code = cd(commands->argv, g_info.env);
	if (!ft_strncmp(name, g_info.bltn[2], 4))
		code = pwd();
	return (code);
}

static void	child(int fd[2], t_command *commands, int fd_out)
{
	int	temp;

	if (fd_out < 0)
	{
		close(fd[OUTPUT_END]);
		dup2(fd[INPUT_END], STDOUT_FILENO);
		close(fd[INPUT_END]);
	}
	else
		dup2(fd_out, STDOUT_FILENO);
	temp = chk_builtin(commands);
	if (temp == NONBLTN)
	{
		g_info.last_prcs = execve(commands->name, commands->argv, g_info.env);
		error(commands->name);
	}
	else
		g_info.last_prcs = temp;
}

static int	pipeline(t_command *commands, int fd[2])
{
	pid_t	pid;
	int		fd_redir[2];
	char	**doc;

	if (pipe(fd))
		return (-1);
	doc = NULL;
	redirect(commands->redirects, fd_redir, &doc);
	if (check_fd_ret(fd_redir, fd, &doc))
		return (-1);
	pid = fork();
	if (!pid)
		child(fd, commands, fd_redir[1]);
	else if (pid > 0)
	{
		close(fd[INPUT_END]);
		if (fd_redir[0] == STD_VAL)
			dup2(fd[OUTPUT_END], STDIN_FILENO);
		close(fd[OUTPUT_END]);
	}
	else
		return (-1);
	return (pid);
}

static int	last_fork(t_command *commands, int fd[2])
{
	int	pid;
	int	status;

	pid = pipeline(commands, fd);
	if (pid > 0)
		waitpid(pid, &status, 0);
	else
		return (-1);
	if (WIFEXITED(status))
		g_info.last_prcs = WEXITSTATUS(status);
	return (0);
}

int	pipex(t_command *commands)
{
	int		fd[2];
	int		status;
	int		pid;

	while (lst_len(commands) - 1)
	{
		pid = pipeline(commands, fd);
		if (pid > 0)
			waitpid(pid, &status, 0);
		else
			return (-1);
		if (WIFEXITED(status))
			g_info.last_prcs = WEXITSTATUS(status);
		commands = commands->next;
	}
	last_fork(commands, fd);
	return (0);
}
