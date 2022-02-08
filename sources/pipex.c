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

static int	child(int fd[2], t_command *commands, int fd_out)
{
	int	temp;
	int	pid;

	pid = 0;
	if (fd_out != STD_VAL)
		dup2(fd_out, STDOUT_FILENO);
	else
		dup2(fd[INPUT_END], STDOUT_FILENO);
	temp = chk_builtin(commands, fd);
	if (temp == NONBLTN)
	{
		pid = fork();
		if (pid)
			return (pid);
		close(fd[OUTPUT_END]);
		if (fd_out == STD_VAL)
			dup2(fd[INPUT_END], STDOUT_FILENO);
		close(fd[INPUT_END]);
		g_info.last_prcs = execve(commands->name, commands->argv, g_info.env);
		error(commands->name, 0);
	}
	else
		g_info.last_prcs = temp;
	return (pid);
}

static int	pipeline(t_command *commands, int fd[2], char **doc)
{
	pid_t	pid;
	int		fd_redir[2];

	redirect(commands->rdrct, fd_redir, &doc);
	if (check_fd_ret(fd_redir, fd, &doc))
		return (-1);
	pid = child(fd, commands, fd_redir[1]);
	if (pid < 0)
		return (-1);
	if (pid > 0)
	{
		close(fd[INPUT_END]);
		if (fd_redir[0] == STD_VAL)
			dup2(fd[OUTPUT_END], STDIN_FILENO);
		close(fd[OUTPUT_END]);
	}
	return (pid);
}

int	pipex(t_command *commands)
{
	int	fd[2];
	int	status;
	int	pid;

	while (lst_len(commands) - 1) // здесь сегается
	{
		if (pipe(fd))
			return (-1);
		pid = pipeline(commands, fd, NULL);
		if (pid > 0)
			waitpid(pid, &status, 0);
		else
			return (-1);
		if (WIFEXITED(status))
			g_info.last_prcs = WEXITSTATUS(status);
		commands = commands->next;
	}
	last_fork(commands);
	return (0);
}
