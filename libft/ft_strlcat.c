/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcat.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bemmanue <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/18 15:10:15 by bemmanue          #+#    #+#             */
/*   Updated: 2021/05/04 13:06:03 by bemmanue         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t	ft_strlcat(char *dst, const char *src, size_t dstsize)
{
	size_t	d;
	size_t	s;
	size_t	i;

	s = 0;
	d = ft_strlen(dst);
	if (d < dstsize)
		i = d;
	else
		return (dstsize + ft_strlen(src));
	while (*dst)
		dst++;
	while (src[s] != '\0' && s + i < dstsize - 1)
	{
		if (dstsize - i > 0)
		{
			*dst++ = src[s];
			s++;
		}
	}
	*dst = '\0';
	return (i + ft_strlen(src));
}
