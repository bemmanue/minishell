
#ifndef PARSER_H
# define PARSER_H

# include <stdio.h>
# include <string.h>
# include <minishell.h>
# include <stdbool.h>

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

# ifndef INFO
#  define INFO
typedef struct s_info
{
    int		std_fd[2];
    int		error;
    int		last_prcs;
    char	*file;
    char	**env;
    char	**bltn;
}t_info;
# endif

# define MEMORY_ERROR	"minishell: Cannot allocate memory"
# define TOKEN_ERROR	"minishell: syntax error near unexpected token "
# define PIPE_ERROR		"minishell: syntax error near unexpected token `|'"
# define NEWLINE_ERROR  "minishell: syntax error near unexpected token `newline'"



t_info  g_info;

t_command	*parse_string(char *str);
void		check_correct_use_of_pipes(char *str);

char		*get_command_line(char **str);
t_list		*split_command_line(char *str);

void		write_command(t_command *command, t_list *list);
void		fill_command(t_command	*command, t_list *list);
t_command	*get_last_command(t_command *command);
t_command	*new_command(t_list *list);
void 		*add_new_command(t_command **command, t_list *list);

void		open_quotes(char **str);
void		open_dollar(char **str);
char		*expand(char *argv);

char 		*get_argument(char *str);
char 		*get_redirect(char *str);
char		*get_dollar(char *str);
char		*get_quotes_content(char *str);

int			skip_argument(char *str);
int			skip_quotes(char *str);
int			skip_redirect(char *str);

void		count_arguments(t_list *list, int *argv_number, int *rdrct_number);
char		*add_full_path(char *str, char **path);
int			is_builtin_command(char *name);
void		free_array(char **array);

void	    *raise_error(char *message, int code);
void		*parser_error(t_command *command);

#endif
