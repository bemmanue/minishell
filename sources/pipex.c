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
	if (!ft_strncmp(name, g_info.bltn[0], max(name, g_info.bltn[0])))
		code = echo(argc, commands->argv);
	if (!ft_strncmp(name, g_info.bltn[0], max(name, g_info.bltn[0])))
		code = cd(commands->argv, g_info.env);
	if (!ft_strncmp(name, g_info.bltn[0], max(name, g_info.bltn[0])))
		code = pwd();
//	if (!ft_strncmp(name, g_info.bltn[0], max(name, g_info.bltn[0])))
//		code = export(argc, commands->argv);
//	if (!ft_strncmp(name, g_info.bltn[0], max(name, g_info.bltn[0])))
//		code = unset(argc, commands->argv);
//	if (!ft_strncmp(name, g_info.bltn[0], max(name, g_info.bltn[0])))
//		code = env(argc, commands->argv);
//	if (!ft_strncmp(name, g_info.bltn[0], max(name, g_info.bltn[0])))
//		code = exit(argc, commands->argv);
	return (code);
}

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
	if (chk_builtin(commands))
	{

		execve(commands->name, commands->argv, NULL);
		write(2, "minishell error: exec\n", 22);
		error(NULL);
	}
}

static int	pipeline(t_command *commands, int fd[2])
{
	pid_t	pid;
	int		fd_redir[2];
	char	**doc;

	if (pipe(fd))
		return (-1);
	redirect(commands->redirects, fd_redir, &doc);
	//возможно хорошая мысль
	//вставить сюда проверку фдшников и выход?
	if (fd_redir[0] > 0)
		dups(fd_redir[0], &doc, fd);
	else if (fd_redir[0] != -6 || (fd_redir[1] < 0 && fd_redir[1] != -6))
		return (-1);
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
		return (-1);
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
		else
			return (errno);
		counter++;
	}
	last_fork(commands);
	return (0);
}
