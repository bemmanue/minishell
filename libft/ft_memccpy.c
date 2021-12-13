/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memccpy.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bemmanue <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/23 19:20:18 by bemmanue          #+#    #+#             */
/*   Updated: 2021/04/23 21:00:38 by bemmanue         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memccpy(void *dst, const void *src, int c, size_t n)
{
	unsigned char		b;
	unsigned char		*d;
	unsigned const char	*s;

	b = c;
	d = dst;
	s = src;
	if (c > 255)
		c %= 256;
	while (n != 0)
	{
		*d++ = *s++;
		if (*(d - 1) == b)
			return (d);
		n--;
	}
	return (NULL);
}
