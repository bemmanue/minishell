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

void	free_str(char *s1, char *s2, char *s3)
{
	if (s1)
		free(s1);
	if (s2)
		free(s2);
	if (s3)
		free(s3);
}

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
	if (!new)
		raise_error(MEMORY_ERROR, NULL);
	free_str(temp, first_part, second_part);
	return (new);
}

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
	free_str(temp, content, NULL);
}

void	disclose_dollar(char **str, int *i)
{
	char	*dollar;
	char	*content;
	char	*temp;

	dollar = get_dollar(&(*str)[*i]);
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
	else
		content = getenv(dollar);
	temp = *str;
	*str = insert_content(*str, *i, *i + 1 + ft_strlen(dollar), content);
	*i += (int)ft_strlen(dollar);
	free_str(temp, dollar, content);
}

void	open_quotes(char **str)
{
	int		i;

	i = 0;
	while (!g_info.error && (*str)[i])
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
	while (!g_info.error && (*str)[i])
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
