/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dwillard <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/27 18:34:43 by dwillard          #+#    #+#             */
/*   Updated: 2022/01/27 18:34:57 by dwillard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

void	error_pipex(void)
{
	ft_putendl_fd(strerror(errno), 2);
}

int	chk_builtin(t_command *commands, int fd[2])
{
	char	*name;
	int		code;

	(void)fd;
	code = NONBLTN;
	name = commands->name;
	if (!ft_strncmp(name, g_info.bltn[0], 5))
		code = ft_echo(commands->argv);
	else if (!ft_strncmp(name, g_info.bltn[1], 3))
		code = ft_cd(commands->argv, g_info.env);
	else if (!ft_strncmp(name, g_info.bltn[2], 4))
		code = ft_pwd(commands->argv);
	else if (!ft_strncmp(name, g_info.bltn[3], 4))
		code = ft_export(commands->argv, &g_info.env);
	else if (!ft_strncmp(name, g_info.bltn[4], 4))
		code = ft_unset(commands->argv, &g_info.env);
	else if (!ft_strncmp(name, g_info.bltn[5], 4))
		code = ft_env(commands->argv, g_info.env);
	else if (!ft_strncmp(name, g_info.bltn[6], 5))
		code = ft_exit(commands->argv);
	return (code);
}

void	dups(char ***doc, int fd_redir[2])
{
	char	**heredoc;
	int		counter;

	counter = 0;
	heredoc = *doc;
	if (fd_redir[0] != HEREDOC && fd_redir[0] != STD_VAL)
		dup2(fd_redir[0], STDIN_FILENO);
	else if (fd_redir[0] == HEREDOC)
	{
		while (heredoc[counter])
		{
			ft_putendl_fd(heredoc[counter], STDIN_FILENO);
			counter++;
		}
		free_arr(doc);
	}
	if (fd_redir[0] != HEREDOC && fd_redir[0] != STD_VAL)
		close(fd_redir[0]);
	if (fd_redir[1] != STD_VAL)
	{
		dup2(fd_redir[1], STDOUT_FILENO);
		close(fd_redir[1]);
	}
}

int	check_fd_ret(int fd_redir[2], int fd[2], char ***doc)
{
	if (fd_redir[0] < 0 || fd_redir[1] < 0)
	{
		if (*doc)
			free_arr(doc);
		if (fd)
		{
			close(fd[INPUT_END]);
			close(fd[OUTPUT_END]);
		}
		if (fd_redir[0] < 0 && fd_redir[1] != STD_VAL)
			close(fd_redir[1]);
		if (fd_redir[1] < 0 && fd_redir[0] != STD_VAL)
			close(fd_redir[0]);
		error_pipex();
		return (-1);
	}
	if (fd_redir[0] != STD_VAL || fd_redir[1] != STD_VAL)
		dups(doc, fd_redir);
	return (0);
}
