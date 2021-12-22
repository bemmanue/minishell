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

#include "../minishell.h"

static int	child(t_command *commands, int fd[2])
{
	pid_t	pid;

	if (pipe(fd))
		return (errno);
	pid = fork();
	if (!pid)
	{
		close(fd[OUTPUT_END]);
		dup2(fd[INPUT_END], STDOUT_FILENO);
		close(fd[INPUT_END]);
		execve(commands->name, commands->argv, NULL);
		write(2, "Error: exec\n", 12);
		exit(errno);
	}
	else if (pid > 0)
	{
		close(fd[INPUT_END]);
		dup2(fd[OUTPUT_END], STDIN_FILENO);
		close(fd[OUTPUT_END]);
	}
	else
		return (errno);
	return (pid);
}

static int	last_fork(t_command *command, int backup[2])
{
	int	pid;
	int	status;

	if (ft_strncmp(command->name, "cd", 3))
		return (cd)
	pid = fork();
	if (pid < 0)
		return (errno);
	else if (!pid)
	{
		dup2(backup[1], STDOUT_FILENO);
		execve(command->name, command->argv, NULL);
		write(2, "Error: exec\n", 12);
		exit(errno);
	}
	else
		waitpid(pid, &status, 0);
	return (status);
}

static int	pipeline(t_command *commands, char **envp, int backup[2])
{
	int		counter;
	int		fd[2];
	int		status;
	int		pid;

	counter = 0;
	while (counter < lst_len(commands) - 1)
	{
		pid = child(commands, fd);
		waitpid(pid, &status, 0);
		counter++;
	}
	last_fork(commands, backup);
	return (0);
}

int	pipex(t_command *commands, char **envp)
{
	int		backup[2];

	backup[0] = dup(STDIN_FILENO);
	backup[1] = dup(STDOUT_FILENO);
	pipeline(commands, envp, backup);
	return (0);
}
