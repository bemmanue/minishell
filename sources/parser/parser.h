
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

# define PIPE_ERROR		1
# define MEMORY_ERROR	2

int	g_error; //удалить и заменить все вхождения на элемент глобальной структуры

t_command	*parse_string(char *str);
void		check_correct_use_of_pipes(char *str);

char		*get_command_line(char **str);
t_list		*split_command_line(char *str);

void 		*add_new_command(t_command **command, t_list *list);
t_command	*new_command(t_list *list);
void		fill_command(t_command	*command, t_list *list);
void		write_command(t_command *command, t_list *list);

char		*expand(char *argv);
void		count_arguments(t_list *list, int *argv_number, int *rdrct_number);
void		*open_quotes(char *str);
void		open_dollar(char **str);
char		*put_instead_of(char *str, int i, int j, char *env);
char		*get_content(char *str);

char 		*get_argument(char *str);
char 		*get_redirect(char *str);

char		*get_dollar(char *str);
char		*get_env(char **envp, char *var);
char		*add_full_path(char *str, char **path);
char		**split_path(char **envp);
int			is_builtin_command(char *name);
void		*raise_error(int code);
void		*ft_parser_error(void);
t_command	*get_last_command(t_command *command);

int			skip_argument(char *str);
int			skip_quotes(char *str);
int			skip_redirect(char *str);

void		free_array(char **array);

#endif
