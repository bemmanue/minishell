/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   open.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bemmanue <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/30 19:21:04 by bemmanue          #+#    #+#             */
/*   Updated: 2022/01/30 19:21:09 by bemmanue         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <parser.h>

void	disclose_quotes(char **str, int *i)
{
	char	*content;
	char	*temp;

	content = get_quotes_content(&(*str)[*i]);
	if (!content)
		return ;
	temp = *str;
	*str = insert_content(*str, *i, *i + 2 + ft_strlen(content), content);
	*i += (int)ft_strlen(content) + 2;
	ft_free_strs(temp, content, NULL);
}

void	disclose_dollar(char **str, int *i)
{
	char	*dollar;
	char	*content;
	char	*temp;

	dollar = get_dollar_for_expand(&(*str)[*i]);
	if (!dollar)
		return ;
	if (*dollar == '?')
	{
		content = ft_itoa(g_info.last_prcs);
		if (!content)
		{
			raise_error(MEMORY_ERROR, NULL);
			free(dollar);
			return ;
		}
	}
	else if (ft_getenv(g_info.env, dollar))
		content = ft_strdup(ft_getenv(g_info.env, dollar));
	else
		content = ft_strdup("");
	temp = *str;
	*str = insert_content(*str, *i, *i + 1 + ft_strlen(dollar), content);
	*i += (int)ft_strlen(content);
	ft_free_strs(temp, dollar, content);
}

void	expand_quotes(char **str)
{
	int		i;

	i = 0;
	while (!g_info.error && (*str)[i])
	{
		if (ft_strchr("'\"", (*str)[i]))
			disclose_quotes(str, &i);
		i++;
	}
}

void	expand_dollar(char **str)
{
	bool	double_quote;
	int		i;

	i = 0;
	double_quote = 0;
	while (!g_info.error && (*str)[i])
	{
		if ((*str)[i] == '\'' && !double_quote)
			i += skip_quotes(str[i]);
		else if ((*str)[i] == '"' && !double_quote)
			double_quote = 1;
		else if ((*str)[i] == '"' && double_quote)
			double_quote = 0;
		while ((*str)[i] == '$' && !ft_strchr(" \t\v\0", (*str)[i + 1]))
			disclose_dollar(str, &i);
		i++;
	}
}

char	*expand(char *argument)
{
	char	*new;

	new = ft_strdup(argument);
	if (!new)
		raise_error(MEMORY_ERROR, NULL);
	expand_dollar(&new);
	expand_quotes(&new);
	return (new);
}
