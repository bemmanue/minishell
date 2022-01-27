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

void	dups(int fd_in, char ***doc, int fd[2])
{
	char	**heredoc;

	close(fd[INPUT_END]);
	close(fd[OUTPUT_END]);
	heredoc = *doc;
	if (fd_in != HEREDOC)
		dup2(fd_in, STDIN_FILENO);
	else
	{
		while (*heredoc)
		{
			write(STDIN_FILENO, *heredoc, ft_strlen(*heredoc));
			heredoc += sizeof(char *);
		}
		free_arr(doc);
	}
	if (fd_in != HEREDOC)
		close(fd_in);
}