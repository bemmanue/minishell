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
	if (fd_out == STD_VAL)
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
		pid = fork();
		if (pid)
			return (pid);
		g_info.last_prcs = execve(commands->name, commands->argv, g_info.env);
		error(commands->name);
	}
	else
		g_info.last_prcs = temp;
	return (pid);
}

static int	pipeline(t_command *commands, int fd[2])
{
	pid_t	pid;
	int		fd_redir[2];
	char	**doc;

	if (pipe(fd))
		return (-1);
	doc = NULL;
	redirect(commands->rdrct, fd_redir, &doc);
	if (check_fd_ret(fd_redir, fd, &doc))
		return (-1);
	pid = child(fd, commands, fd_redir[1]);
	close(fd[INPUT_END]);
	if (fd_redir[0] == STD_VAL)
		dup2(fd[OUTPUT_END], STDIN_FILENO);
	close(fd[OUTPUT_END]);
	if (pid < 0)
		return (-1);
	return (pid);
}

static int	last_pipeline(t_command *commands, int fd[2], int iter)
{
	pid_t	pid;
	int		fd_redir[2];
	char	**doc;

	if (pipe(fd))
		return (-1);
	doc = NULL;
	redirect(commands->rdrct, fd_redir, &doc);
	if (check_fd_ret(fd_redir, fd, &doc))
		return (-1);
	if (fd_redir[1] == STD_VAL)
		fd_redir[1] = g_info.std_fd[1];
	pid = child(fd, commands, fd_redir[1]);
	close(fd[INPUT_END]);
	if (fd_redir[0] == STD_VAL && iter)
		dup2(fd[OUTPUT_END], STDIN_FILENO);
	close(fd[OUTPUT_END]);
	if (pid < 0)
		return (-1);
	return (pid);
}

static int	last_fork(t_command *commands, int fd[2], int iter)
{
	int	pid;
	int	status;

	pid = last_pipeline(commands, fd, iter);
	if (pid > 0)
		waitpid(pid, &status, 0);
	else if (pid < 0)
		return (-1);
	if (WIFEXITED(status))
		g_info.last_prcs = WEXITSTATUS(status);
	return (0);
}

int	pipex(t_command *commands)
{
	int	fd[2];
	int	status;
	int	pid;
	int	counter;

	counter = 0;
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
		counter++;
	}
	last_fork(commands, fd, counter);
	return (0);
}
