/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strrchr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bemmanue <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/20 14:38:56 by bemmanue          #+#    #+#             */
/*   Updated: 2021/04/20 15:21:09 by bemmanue         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strrchr(const char *s, int c)
{
	int	i;

	i = 0;
	if (c > 255)
		c %= 256;
	while (*s)
	{
		i++;
		s++;
	}
	while (i-- > 0)
	{
		if (*s-- == (char) c)
			return ((char *)(s + 1));
	}
	if (*s == c)
		return ((char *)s);
	return (NULL);
}
