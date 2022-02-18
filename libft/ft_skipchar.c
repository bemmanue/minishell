/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_skipchar.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bemmanue <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/27 17:23:08 by bemmanue          #+#    #+#             */
/*   Updated: 2022/01/27 17:23:10 by bemmanue         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static char	*write_new(const char *str, char *skip, int new_len)
{
	char	*new;
	int		str_index;
	int		new_index;

	str_index = 0;
	new_index = 0;
	new = malloc(sizeof(char) * (new_len + 1));
	if (!new)
		return (NULL);
	while (str[str_index] && str_index < new_len)
	{
		if (!ft_strchr(skip, str[str_index]))
			new[new_index++] = str[str_index];
		str_index++;
	}
	new[new_index] = '\0';
	return (new);
}

static int	count_new_len(const char *str, char *skip)
{
	int		new_len;
	int		i;

	i = 0;
	new_len = 0;
	while (str[i])
	{
		if (!ft_strchr(skip, str[i]))
			new_len++;
		i++;
	}
	return (new_len);
}

char	*ft_skipchar(const char *str, char *skip)
{
	char	*new;
	int		new_len;

	new_len = count_new_len(str, skip);
	new = write_new(str, skip, new_len);
	return (new);
}
