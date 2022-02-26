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

# define INPUT_END 1
# define OUTPUT_END 0
# define NO_FILE -1
# define NO_READ -2
# define NO_WRIT -3
# define MEM_ERR -4
# define OPN_ERR -5
# define HEREDOC 100
# define SIG_END 130
# define SIG_BCK 131
# define STD_VAL 200
# define NONBLTN 1000

extern t_info	g_info;

int			command_center(char *input, char ***envp);
void		dups(int fd[2]);
void		error_pipex(char *str);
void		error(char *str, int err);
int			pipex(t_command *commands);
int			last_fork(t_command *commands);
int			get_exit(t_command *commands);
int			command_len(t_command *command);
int			chk_builtin(t_command *commands);
char		*ft_getenv(char **envp, char *name);
int			check_fd_ret(int fd_redir[2], int fd[2]);
int			*redirect(char **red_arr, int fd_pair[2]);
int			control(char *delimiter);
void		rl_replace_line(const char *buffer, int val);
void		fill_fd(int *fd_arr, int count);
void		set_signals(void);
void		signal_in_pipes(void);
void		signal_in_child(void);
void		cancel_cmd(int signo);
void		ft_signal_cltr_c(int sig);

#endif
