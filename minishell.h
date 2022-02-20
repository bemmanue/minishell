/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dwillard <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/17 18:22:15 by dwillard          #+#    #+#             */
/*   Updated: 2022/01/17 18:23:33 by dwillard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

// проверить в основной части, не в парсере:
//	if (!path)
//      "No such file or directory";
//  else if (access(name, F_OK))
//      "command not found";
//  else
//      do command;

# include <builtin.h>
# include <libft.h>
# include <parser.h>
# include <readline/readline.h>
# include <readline/history.h>
# include <sys/wait.h>
# include <string.h>
# include <signal.h>
# include <errno.h>
# include <err.h>

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

# ifndef COMMAND
#  define COMMAND

typedef struct s_command
{
	char	*name;
	char	**argv;
	char	**rdrct;
	void	*next;
}			t_command;
# endif

# ifndef INFO
#  define INFO

typedef struct s_info
{
	int		std_fd[2];
	int		error;
	int		last_prcs;
	char	*file;
	char	*minidir;
	char	**env;
	char	**bltn;
}			t_info;
# endif

extern t_info	g_info;

void		dups(int fd[2]);
void		error_pipex(void);
void		set_signals(void);
void		signal_in_pipes(void);
void		signal_in_child(void);
void		error(char *str, int err);
int			pipex(t_command *commands);
int			last_fork(t_command *commands);
int			command_len(t_command *command);
int			chk_builtin(t_command *commands);
int			check_fd_ret(int fd_redir[2], int fd[2]);
int			*redirect(char **red_arr, int fd_pair[2]);
int			command_center(char *input, char ***envp);
void		rl_replace_line(const char *buffer, int val);

#endif
