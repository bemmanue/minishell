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

t_list	*add_argument(char **str)
{
	t_list	*new;

	new = ft_lstnew(get_argument(*str));
	*str += skip_argument(*str);
	return (new);
}

t_list	*add_redirect(char **str)
{
	t_list	*new;

	new = ft_lstnew(get_redirect(*str));
	*str += skip_redirect(*str);
	return (new);
}

t_list	*add_dollar(char **str)
{
	t_list	*new;
	char	*dollar;

	new = NULL;
	dollar = get_dollar(*str);
	if (!dollar)
		return (NULL);
	if (*dollar == '?' || getenv(dollar))
	{
		new = ft_lstnew(get_argument(*str));
		*str += skip_argument(*str);
	}
	else
		*str += ft_strlen(dollar) + 1;
	free(dollar);
	return (new);
}

void	split_command_line(char *str, t_list *list[2])
{
	t_list	*new;

	list[0] = NULL;
	list[1] = NULL;
	while (!strchr("|\0", *str) && !g_info.error)
	{
		if (strchr(" \t\v", *str))
			str++;
		else
		{
			if (*str == '$')
			{
				new = add_dollar(&str);
				if (new)
					ft_lstadd_back(&list[0], new);
			}
			else if (strchr("<>", *str))
			{
				new = add_redirect(&str);
				if (new)
					ft_lstadd_back(&list[1], new);
			}
			else
			{
				new = add_argument(&str);
				if (new)
					ft_lstadd_back(&list[0], new);
			}
		}
	}
}

char	*get_command_line(char **str)
{
	char	*command_line;

	command_line = *str;
	while (**str && **str != '|' && !g_info.error)
	{
		if (strchr("'\"", **str))
			(*str) += skip_quotes(*str);
		(*str)++;
	}
	if (**str == '|')
		(*str)++;
	return (command_line);
}
