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

void	add_argument(char **str, t_list **list)
{
	t_list	*new;

	new = ft_lstnew(get_argument(*str));
	if (new)
		ft_lstadd_back(list, new);
	*str += skip_argument(*str);
}

void	add_redirect(char **str, t_list **list)
{
	t_list	*new;

	new = ft_lstnew(get_redirect(*str));
	if (new)
		ft_lstadd_back(list, new);
	*str += skip_redirect(*str);
}

void	add_dollar(char **str, t_list **list)
{
	t_list	*new;
	char	*dollar;

	new = NULL;
	dollar = get_dollar(*str);
	if (!dollar)
		return ;
	if (*dollar == '?' || ft_getenv(g_info.env, dollar))
	{
		new = ft_lstnew(get_argument(*str));
		if (new)
			ft_lstadd_back(list, new);
		*str += skip_argument(*str);
	}
	else
		*str += ft_strlen(dollar) + 1;
	free(dollar);
}

void	split_command_line(char *str, t_list *list[2])
{
	list[0] = NULL;
	list[1] = NULL;
	while (!ft_strchr("|\0", *str) && !g_info.error)
	{
		if (ft_strchr(" \t\v", *str))
			str++;
		else if (ft_strchr("<>", *str))
			add_redirect(&str, &list[1]);
		else if (*str == '$')
			add_dollar(&str, &list[0]);
		else
			add_argument(&str, &list[0]);
	}
}

char	*get_command_line(char **str)
{
	char	*command_line;

	command_line = *str;
	while (**str && **str != '|' && !g_info.error)
	{
		if (ft_strchr("'\"", **str))
			(*str) += skip_quotes(*str);
		(*str)++;
	}
	if (**str == '|')
		(*str)++;
	return (command_line);
}
