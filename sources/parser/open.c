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

#include "parser.h"

char	*insert_content(char *str, int start, int end, char *content)
{
	char	*first_part;
	char	*second_part;
	char	*temp;
	char	*new;

	first_part = strndup(str, start);
	second_part = strdup(&str[end]);
	temp = ft_strjoin(first_part, content);
	new = ft_strjoin(temp, second_part);
	free(temp);
	free(first_part);
	free(second_part);
	return (new);
}

void	disclose_quotes(char **str, int *i)
{
	char	*content;
	char	*temp;

	content = get_quotes_content(&(*str)[*i]);
	temp = *str;
	*str = insert_content(*str, *i, *i + 2 + ft_strlen(content), content);
	free(temp);
	*i += ft_strlen(content) + 2;
}

void	disclose_dollar(char **str, int *i)
{
	char	*dollar;
	char	*content;
	char	*temp;

	dollar = get_dollar(&(*str)[*i]);
	content = getenv(dollar);
	temp = *str;
	*str = insert_content(*str, *i, *i + 1 + ft_strlen(dollar), content);
	free(temp);
	*i += ft_strlen(dollar);
}

void	open_quotes(char **str)
{
	int		i;

	i = 0;
	while ((*str)[i])
	{
		if (strchr("'\"", (*str)[i]))
			disclose_quotes(str, &i);
		i++;
	}
}

void	open_dollar(char **str)
{
	bool	double_quote;
	int		i;

	i = 0;
	double_quote = 0;
	while ((*str)[i])
	{
		if ((*str)[i] == '\'' && !double_quote)
			i += skip_quotes(str[i]);
		else if ((*str)[i] == '"' && !double_quote)
			double_quote = 1;
		else if ((*str)[i] == '"' && double_quote)
			double_quote = 0;
		if ((*str)[i] == '$' && !strchr(" '\"\t\v\0", (*str)[i + 1]))
			disclose_dollar(str, &i);
		i++;
	}
}
