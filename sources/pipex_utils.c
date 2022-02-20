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

static void	err_utils(void)
{
	if (g_info.error == (uint8_t)NO_FILE)
		ft_putendl_fd("No such file or directory", 2);
	if (g_info.error == (uint8_t)NO_READ)
		ft_putendl_fd("Permission denied", 2);
	if (g_info.error == (uint8_t)NO_WRIT)
		ft_putendl_fd("Permission denied", 2);
	if (g_info.error == (uint8_t)MEM_ERR)
		ft_putendl_fd("Memory error", 2);
	if (g_info.error == (uint8_t)OPN_ERR)
		ft_putendl_fd("Permission denied", 2);
}

void	error_pipex(char *str)
{
	ft_putstr_fd("minishell: ", 2);
	if (str)
	{
		ft_putstr_fd(str, 2);
		ft_putstr_fd(": ", 2);
	}
	if (!g_info.error)
		ft_putendl_fd(strerror(errno), 2);
	else
		err_utils();
}

int	chk_builtin(t_command *commands)
{
	char	*name;
	int		code;

	code = NONBLTN;
	name = commands->name;
	if (!ft_strncmp(name, g_info.bltn[0], 5))
		code = ft_echo(commands->argv);
	else if (!ft_strncmp(name, g_info.bltn[1], 3))
		code = ft_cd(commands->argv, g_info.env);
	else if (!ft_strncmp(name, g_info.bltn[2], 4))
		code = ft_pwd();
	else if (!ft_strncmp(name, g_info.bltn[3], 4))
		code = ft_export(commands->argv, &g_info.env);
	else if (!ft_strncmp(name, g_info.bltn[4], 4))
		code = ft_unset(commands->argv, &g_info.env);
	else if (!ft_strncmp(name, g_info.bltn[5], 4))
		code = ft_env(commands->argv, g_info.env);
	else if (!ft_strncmp(name, g_info.bltn[6], 5))
		code = ft_exit(commands->argv);
	if (code != NONBLTN)
		g_info.last_prcs = code;
	return (code);
}

void	dups(int fd_redir[2])
{
	int	fd;

	if (fd_redir[0] != STD_VAL && fd_redir[0] != HEREDOC)
		dup2(fd_redir[0], STDIN_FILENO);
	else if (fd_redir[0] == HEREDOC)
	{
		fd = open(g_info.minidir, O_RDONLY);
		dup2(fd, STDIN_FILENO);
		close(fd);
	}
	if (fd_redir[0] != STD_VAL && fd_redir[0] != HEREDOC)
		close(fd_redir[0]);
	if (fd_redir[1] != STD_VAL)
	{
		dup2(fd_redir[1], STDOUT_FILENO);
		close(fd_redir[1]);
	}
}

int	check_fd_ret(int fd_redir[2], int fd[2])
{
	if (fd_redir[0] < 0 || fd_redir[1] < 0)
	{
		if (fd)
		{
			close(fd[INPUT_END]);
			close(fd[OUTPUT_END]);
		}
		if (fd_redir[0] < 0 && fd_redir[1] != STD_VAL)
			close(fd_redir[1]);
		if (fd_redir[1] < 0 && fd_redir[0] != STD_VAL)
			close(fd_redir[0]);
		error_pipex(NULL);
		return (-1);
	}
	if (fd_redir[0] != STD_VAL || fd_redir[1] != STD_VAL)
		dups(fd_redir);
	return (0);
}
