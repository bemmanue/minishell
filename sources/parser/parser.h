
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
# define NEWLINE_ERROR  "minishell: syntax error near unexpected token `newline'"

t_command	*parse_string(char *str);
void		check_correct_use_of_pipes(char *str);

char		*get_command_line(char **str);
t_list		*split_command_line(char *str);

t_command	*new_command(t_list *list);
void		*free_command(t_command *command);
t_command	*get_last_command(t_command *command);
void		fill_command(t_command	*command, t_list *list);
void 		*add_new_command(t_command **command, t_list *list);

char		*expand(char *argv);
void		expand_quotes(char **str);
void		expand_dollar(char **str);

char		*get_dollar(char *str);
char 		*get_argument(char *str);
char 		*get_redirect(char *str);
char		*get_quotes_content(char *str);

int			skip_quotes(char *str);
int			skip_redirect(char *str);
int			skip_argument(char *str);

void		free_array(char **array);
int			is_builtin_command(char *name);
char		*add_full_path(char *str, char **path);
void	    free_strs(char *s1, char *s2, char *s3);
void	    *raise_error(char *message, char *str, int code);
char	    *insert_content(char *str, int start, int end, char *content);
void		count_arguments(t_list *list, int *argv_number, int *rdrct_number);

#endif
