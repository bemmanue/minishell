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

void	dups(int fd_in, char ***doc, int fd[2])
{
	char	**heredoc;

	heredoc = *doc;
	if (fd_in != HEREDOC && fd_in != STD_VAL)
		dup2(fd_in, STDIN_FILENO);
	else if (fd_in == HEREDOC)
	{
		while (*heredoc)
		{
			write(STDIN_FILENO, *heredoc, ft_strlen(*heredoc));
			heredoc += sizeof(char *);
		}
		free_arr(doc);
	}
	if (fd[1] != STD_VAL)
	{
		dup2(fd[1], STDOUT_FILENO);
		close(fd[1]);
	}
	if (fd_in != HEREDOC && fd_in != STD_VAL)
		close(fd_in);
}

int	check_fd_ret(int fd_redir[2], int fd[2], char ***doc)
{
	if (fd_redir[0] < 0 || fd_redir[1] < 0)
	{
		if (*doc)
			free_arr(doc);
		close(fd[INPUT_END]);
		close(fd[OUTPUT_END]);
		if (fd_redir[0] < 0 && fd_redir[1] != STD_VAL)
			close(fd_redir[1]);
		else if(fd_redir[1] < 0 && fd_redir[0] != STD_VAL)
			close(fd_redir[0]);
		error_pipex();
		return (-1);
	}
	if (fd_redir[0] != STD_VAL || fd_redir[1] != STD_VAL)
		dups(fd_redir[0], doc, fd_redir);
	return (0);
}
