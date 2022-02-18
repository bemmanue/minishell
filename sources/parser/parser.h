/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bemmanue <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/15 10:38:00 by bemmanue          #+#    #+#             */
/*   Updated: 2022/02/15 14:00:56 by bemmanue         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

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

//t_info g_info;

# define MEMORY_ERROR	"minishell: Cannot allocate memory"
# define TOKEN_ERROR	"minishell: syntax error near unexpected token "
# define NEWL_ERROR  	"minishell: syntax error near unexpected token `newline'"

t_command	*parse_string(char *str);
char		*get_command_line(char **str);
void		split_command_line(char *str, t_list *list[2]);

t_command	*new_command(t_list *list[2]);
void		*free_command(t_command *command);
t_command	*get_last_command(t_command *command);
void		fill_command(t_command *command, t_list *list[2]);
void		*add_new_command(t_command **command, t_list *list[2]);

char		*expand(char *argv);

char		*get_dollar(char *str);
char		*get_argument(char *str);
char		*get_redirect(char *str);
char		*get_quotes_content(char *str);

int			skip_quotes(char *str);
int			skip_redirect(char *str);
int			skip_argument(char *str);

int			is_builtin_command(char *name);
char		*add_full_path(char *str, char **path);
void		free_strs(char *s1, char *s2, char *s3);
void		*raise_error(char *message, char *str, int code);
char		*insert_content(char *str, int start, int end, char *content);

#endif
