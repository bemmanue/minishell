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
# define STD_VAL 200
# define HEREDOC 100
# define NONBLTN 1000

# ifndef COMMAND
#  define COMMAND
typedef struct s_command
{
	char	*name;
	char	**argv;
	char	**rdrct;
	void	*next;
}t_command;
# endif

typedef struct s_env
{
	char	*str;
	void	*next;
}t_env;

struct s_info
{
	int		std_fd[2];
	int		error;
	int		last_prcs;
	char	*file;
	char	**env;
	char	**bltn;
}g_info;

t_env		*lst_new(char *content);

void		lst_add_back(t_env **lst, t_env *new);

int			lst_len(t_command *lst);

int			command_center(char **envp, char *input);

int			pipex(t_command *commands);

void		error_pipex(void);

void		error(char *str);

int			check_fd_ret(int fd_redir[2], int fd[2], char ***doc);

void		dups(int fd_in, char ***doc, int fd[2]);

int			chk_builtin(t_command *command);

int			*redirect(char **red_arr, int *fd_pair, char ***document);

#endif
