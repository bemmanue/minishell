/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bemmanue <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/15 10:38:00 by bemmanue          #+#    #+#             */
/*   Updated: 2022/02/20 13:52:56 by dwillard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSER_H
# define PARSER_H

# include <include.h>

# define MEMORY_ERROR "minishell: Cannot allocate memory"
# define TOKEN_ERROR "minishell: syntax error near unexpected token "
# define NEWL_ERROR "minishell: syntax error near unexpected token `newline'"

t_command	*parse_string(char *str);
char		*get_command_line(char **str);
void		split_command_line(char *str, t_list *list[2]);

t_command	*new_command(t_list *list[2]);
void		*free_command(t_command *command);
t_command	*get_last_command(t_command *command);
void		*add_new_command(t_command **command, t_list *list[2]);

char		*expand(char *argv);

char		*get_dollar(char *str);
char		*get_argument(char *str);
char		*get_redirect(char *str);
char		*get_quotes_content(char *str);

int			skip_quotes(char *str);
int			skip_redirect(char *str);
int			skip_argument(char *str);

char		**get_split_path(void);
int			is_builtin_command(char *name);
char		*add_full_path(char *str, char **path);
void		*raise_error(char *message, char *str);
char		*insert_content(char *str, int start, int end, char *content);

#endif
