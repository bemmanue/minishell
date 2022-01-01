
#ifndef MINISHELL_H
# define MINISHELL_H

# include <readline/readline.h>
# include <readline/history.h>
# include <stdio.h>
# include <sys/wait.h>
# include <string.h>
# include <signal.h>
# include <errno.h>
# include <err.h>
# include "libft/libft.h"
# include "sources/builtin/builtin.h"

# define INPUT_END 1
# define OUTPUT_END 0

typedef struct s_command
{
	char		*name;
	char		**argv;
	void		*next;
}				t_command;

t_command	*parse_string(char **envp, char *file);

int			command_center(char **envp, char *input);

int			pipex(t_command *commands, char **envp);

int			lst_len(t_command *lst);

int			chk_builtin(t_command *command);

#endif
