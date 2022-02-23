/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bemmanue <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/15 14:00:00 by bemmanue          #+#    #+#             */
/*   Updated: 2022/02/15 14:00:00 by bemmanue         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <parser.h>

char	*get_quotes_content(char *str)
{
	char	*content;
	char	quote;
	int		i;

	i = 0;
	quote = *str++;
	while (str[i] && str[i] != quote)
		i++;
	content = ft_strndup(str, i);
	if (!content)
		raise_error(MEMORY_ERROR, NULL, 1);
	return (content);
}

char	*get_dollar(char *str)
{
	char	*dollar;
	int		i;

	i = 1;
	if (str[i] == '?')
		dollar = ft_strdup("?");
	else
	{
		while (!ft_strchr(" $'\"\t\v\0", str[i]))
			i++;
		dollar = ft_strndup(&str[1], i - 1);
	}
	if (!dollar)
		raise_error(MEMORY_ERROR, NULL, 1);
	return (dollar);
}

char	*get_redirect(char *str)
{
	char	*redirect;
	char	*temp;
	int		i;

	i = skip_redirect(str);
	temp = ft_strndup(str, i);
	if (!temp)
		return (raise_error(MEMORY_ERROR, NULL, 1));
	redirect = ft_skipnchar(temp, i, " \t\v");
	if (!redirect)
		raise_error(MEMORY_ERROR, NULL, 1);
	free(temp);
	return (redirect);
}

char	*get_argument(char *str)
{
	char	*argument;
	int		i;

	i = skip_argument(str);
	argument = ft_strndup(str, i);
	if (!argument)
		raise_error(MEMORY_ERROR, NULL, 1);
	return (argument);
}
