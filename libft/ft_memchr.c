/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bemmanue <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/23 15:43:30 by bemmanue          #+#    #+#             */
/*   Updated: 2021/04/23 16:25:55 by bemmanue         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memchr(const void *str, int c, size_t n)
{
	const char	*s;

	s = str;
	if (c > 255)
		c %= 256;
	while (n-- != 0)
	{
		if (*s == c)
			return ((void *)(s));
		s++;
	}
	return (NULL);
}
