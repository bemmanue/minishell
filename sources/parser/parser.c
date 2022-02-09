/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bemmanue <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/28 18:38:50 by bemmanue          #+#    #+#             */
/*   Updated: 2022/01/28 18:38:56 by bemmanue         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"

void	check_correct_use_of_pipes(char *str)
{
	bool	word;
	bool	pipe;

	word = 0;
	pipe = 0;
	while (*str && !g_info.error)
	{
		if (*str == '|' && !word)
		    raise_error(PIPE_ERROR, 1);
		if (*str == '|')
		{
			pipe = 1;
			word = 0;
		}
		else if (!strchr(" \t\v", *str))
		{
			if (*str == '\'' || *str == '"')
				str += skip_quotes(str);
			word = 1;
			pipe = 0;
		}
		str++;
	}
	if (pipe == 1)
	    raise_error(NEWLINE_ERROR, 1);
}

t_command	*parse_string(char *str)
{
	t_command	*command;
	char		*command_line;
	t_list		*list;

	g_info.error = 0;
	command = NULL;
	check_correct_use_of_pipes(str);
	while (*str && !g_info.error)
	{
		command_line = get_command_line(&str);
		list = split_command_line(command_line);
		add_new_command(&command, list);
		ft_lstclear(&list, free);
	}
	if (g_info.error)
		return (parser_error(command));
	return (command);
}
