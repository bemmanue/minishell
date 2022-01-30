/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   command_line.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bemmanue <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/28 18:55:57 by bemmanue          #+#    #+#             */
/*   Updated: 2022/01/28 18:56:20 by bemmanue         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"

t_list	*split_command_line(char *str)
{
	t_list	*list;
	t_list	*new;

	list = NULL;
	while (*str)
	{
		if (strchr(" \t\v", *str))
			str++;
		else
		{
			if (strchr("<>", *str))
			{
				new = ft_lstnew(get_redirect(str));
				str += skip_redirect(str);
			}
			else
			{
				new = ft_lstnew(get_argument(str));
				str += skip_argument(str);
			}
			ft_lstadd_back(&list, new);
		}
	}
	return (list);
}

char	*get_command_line(char **str)
{
	char	*command_line;

	command_line = *str;
	while (**str && **str != '|')
	{
		if (strchr("'\"", **str))
			(*str) += skip_quotes(*str);
		(*str)++;
	}
	if (**str == '|')
		*(*str)++ = '\0';
	return (command_line);
}
