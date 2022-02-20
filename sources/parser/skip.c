/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   skip.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bemmanue <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/15 14:00:00 by bemmanue          #+#    #+#             */
/*   Updated: 2022/02/15 14:00:00 by bemmanue         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"

int	skip_argument(char *str)
{
	int	i;

	i = 0;
	while (!ft_strchr(" <>|\t\v\0", str[i]))
	{
		if (str[i] == '\'' || str[i] == '"')
			i += skip_quotes(&str[i]);
		i++;
	}
	return (i);
}

int	skip_quotes(char *str)
{
	char	quote;
	int		i;

	i = 0;
	quote = str[i++];
	while (str[i] && str[i] != quote)
		i++;
	if (str[i] == '\0')
		raise_error(NEWL_ERROR, NULL, 1);
	return (i);
}

int	skip_redirect(char *str)
{
	char	arrow;
	int		i;

	i = 0;
	arrow = str[i++];
	if (str[i] == arrow)
		i++;
	while (str[i] && ft_strchr(" \t\v", str[i]))
		i++;
	if (!str[i])
		raise_error(NEWL_ERROR, NULL, 1);
	else if (ft_strchr("|<>", str[i]))
		raise_error(TOKEN_ERROR, &str[i], 1);
	else
	{
		while (str[i] && !ft_strchr(" <>|\t\v", str[i]))
		{
			if (str[i] == '\'' || str[i] == '"')
				i += skip_quotes(&str[i]);
			i++;
		}
	}
	return (i);
}
