
#ifndef MINISHELL_H
# define MINISHELL_H

#
# include <readline/readline.h>
# include <readline/history.h>
# include <stdio.h>
# include <stdlib.h>
# include <sys/wait.h>
# include <fcntl.h>
# include <string.h>
# include <unistd.h>
# include <signal.h>
# include "libft/libft.h"
# include <errno.h>
# include <err.h>

typedef struct s_command
{
	char		*name;
	void		*next;
}				t_command;

t_command	*parse_string(char **envp, char *file);

int			command_center(char **envp, char *input);

int			pipex(t_command *commands, char **envp);

#endif
