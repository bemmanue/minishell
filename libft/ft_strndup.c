/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strndup.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bemmanue <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/20 14:27:00 by bemmanue          #+#    #+#             */
/*   Updated: 2022/02/20 14:27:04 by bemmanue         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strndup(const char *s1, size_t n)
{
	char	*new;
	size_t	len;
	size_t	index;

	if (!s1)
		return (NULL);
	len = ft_strlen(s1);
	if (n > len)
		n = len;
	new = malloc(sizeof (char) * (n + 1));
	if (!new)
		return (NULL);
	index = 0;
	while (index < n)
	{
		new[index] = s1[index];
		index++;
	}
	new[index] = '\0';
	return (new);
}
