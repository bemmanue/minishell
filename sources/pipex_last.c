/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_last.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dwillard <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/20 13:53:46 by dwillard          #+#    #+#             */
/*   Updated: 2022/02/20 13:54:10 by dwillard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

static int	get_err(char *str)
{
	char	*temp;

	temp = ft_getenv(g_info.env, "PATH");
	if (!temp)
		return (0);
	free(temp);
	if (!ft_isalpha(*str))
		return (0);
	return (127);
}

static int	child(t_command *commands, int fd_out)
{
	int	pid;

	pid = 0;
	if (fd_out != STD_VAL)
		dup2(fd_out, STDOUT_FILENO);
	else
		dup2(g_info.std_fd[1], STDOUT_FILENO);
	if (chk_builtin(commands) == NONBLTN)
	{
		pid = fork();
		if (pid)
			return (pid);
		g_info.last_prcs = execve(commands->name, commands->argv, g_info.env);
		error(commands->name, get_err(commands->name));
	}
	return (pid);
}

static int	pipeline(t_command *commands)
{
	pid_t	pid;
	int		fd_redir[2];

	if (*redirect(commands->rdrct, fd_redir) == SIG_END)
		return (1);
	if (check_fd_ret(fd_redir, NULL))
		return (-1);
	pid = child(commands, fd_redir[1]);
	if (pid < 0)
		return (-1);
	else if (pid > 0)
		commands->pid = pid;
	return (pid);
}

int	last_fork(t_command *commands)
{
	int		pid;

	pid = pipeline(commands);
	if (pid < 0)
		return (-1);
	if (pid == 1)
		return (1);
	return (0);
}
