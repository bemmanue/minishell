/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dwillard <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/17 18:22:15 by dwillard          #+#    #+#             */
/*   Updated: 2022/02/20 13:52:49 by dwillard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include <include.h>

// проверить в основной части, не в парсере:
//	if (!path)
//      "No such file or directory";
//  else if (access(name, F_OK))
//      "command not found";
//  else
//      do command;

# define INPUT_END 1
# define OUTPUT_END 0
# define NO_FILE -1
# define NO_READ -2
# define NO_WRIT -3
# define MEM_ERR -4
# define OPN_ERR -5
# define HEREDOC 100
# define STD_VAL 200
# define NONBLTN 1000

extern t_info	g_info;

int			lst_len(t_command *lst);

int			command_center(char *input, char ***envp);

int			pipex(t_command *commands);

int			last_fork(t_command *commands);

void		error_pipex(void);

void		error(char *str, int err);

int			check_fd_ret(int fd_redir[2], int fd[2]);

void		dups(int fd[2]);

int			chk_builtin(t_command *commands);

int			*redirect(char **red_arr, int fd_pair[2]);

#endif
