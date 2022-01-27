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
//
//static int	last_fork(t_command *command)
//{
//	int	pid;
//	int	status;
//	int	builtin;
//
//	builtin = chk_builtin(command);
//	if (builtin)
//		return (builtin);
//	pid = fork();
//	if (pid < 0)
//		return (errno);
//	else if (!pid)
//	{
//		execve(command->name, command->argv, NULL);
//		write(2, "Error: exec\n", 12);
//		exit(errno);
//	}
//	else
//		waitpid(pid, &status, 0);
//	return (status);
//}

static void	child(int fd[2], t_command *commands, int fd_out)
{
	if (fd_out < 0)
	{
		close(fd[OUTPUT_END]);
		dup2(fd[INPUT_END], STDOUT_FILENO);
		close(fd[INPUT_END]);
	}
	else
		dup2(fd_out, STDOUT_FILENO);
	//вставить сюда проверки на встроенные функции и сделать условие
	execve(commands->name, commands->argv, NULL);
	write(2, "minishell error: exec\n", 22);
	error(NULL);
}

static int	pipeline(t_command *commands, int fd[2])
{
	pid_t	pid;
	int		fd_redir[2];
	char	**doc;

	if (pipe(fd))
		return (errno);
	redirect(commands->redirects, fd_redir, &doc);
	if (fd_redir[0] > 0)
		dups(fd_redir[0], &doc, fd);
	pid = fork();
	if (!pid)
		child(fd, commands, fd_redir[1]);
	else if (pid > 0 && fd_redir[0] == STD_VAL)
	{
		close(fd[INPUT_END]);
		dup2(fd[OUTPUT_END], STDIN_FILENO);
		close(fd[OUTPUT_END]);
	}
	else
		return (errno);
	return (pid);
}

int	pipex(t_command *commands)
{
	int		counter;
	int		fd[2];
	int		status;
	int		pid;

	counter = 0;
	while (counter < lst_len(commands) - 1)
	{
		pid = pipeline(commands, fd);
		if (pid > 0)
			waitpid(pid, &status, 0);
		counter++;
	}
	last_fork(commands);
	return (0);
}
