/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memmove.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bemmanue <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/22 20:41:37 by bemmanue          #+#    #+#             */
/*   Updated: 2021/04/24 19:05:11 by bemmanue         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memmove(void *dst, const void *src, size_t len)
{
	unsigned char		*d;
	unsigned const char	*s;

	d = dst;
	s = src;
	if (d == s)
		return (dst);
	if (dst > src)
	{
		d = d + (len - 1);
		s = s + (len - 1);
		while (len > 0)
		{
			*d-- = *s--;
			len--;
		}
	}
	while (len != 0)
	{
		*d++ = *s++;
		len--;
	}
	return (dst);
}
