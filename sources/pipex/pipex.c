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

static int	get_err(char *str)
{
	if (!ft_getenv(g_info.env, "PATH"))
		return (0);
	if (!ft_isalpha(*str))
		return (0);
	return (127);
}

static int	child(int fd[2], t_command *commands, int fd_out)
{
	int	pid;

	pid = 0;
	if (fd_out == STD_VAL)
		dup2(fd[INPUT_END], STDOUT_FILENO);
	if (chk_builtin(commands) == NONBLTN)
	{
		pid = fork();
		if (pid)
			return (pid);
		signal_in_child();
		close(fd[OUTPUT_END]);
		if (fd_out == STD_VAL)
			dup2(fd[INPUT_END], STDOUT_FILENO);
		close(fd[INPUT_END]);
		g_info.last_prcs = execve(commands->name, commands->argv, g_info.env);
		error(commands->name, get_err(commands->name));
	}
	return (pid);
}

static int	pipeline(t_command *commands, int fd[2])
{
	pid_t	pid;
	int		*fd_redir;

	fd_redir = commands->fd_redirs;
	if (check_fd_ret(fd_redir, fd, commands))
		return (-1);
	pid = child(fd, commands, fd_redir[1]);
	if (pid < 0)
		return (-1);
	if (pid >= 0)
	{
		close(fd[INPUT_END]);
		dup2(fd[OUTPUT_END], STDIN_FILENO);
		close(fd[OUTPUT_END]);
	}
	return (pid);
}

int	pipex(t_command *commands)
{
	int			fd[2];
	int			status;
	int			pid;

	signal_in_pipes();
	while (command_len(commands) - 1)
	{
		if (pipe(fd))
			return (-1);
		pid = pipeline(commands, fd);
		if (pid == 1)
			return (1);
		else if (pid == SIG_END)
			return (0);
		else if (pid > 0)
			commands->pid = pid;
		else if (pid < 0)
			return (-1);
		if (pid && WIFEXITED(status))
			g_info.last_prcs = WEXITSTATUS(status);
		commands = commands->next;
	}
	if (last_fork(commands) == 1)
		return (1);
	return (0);
}
