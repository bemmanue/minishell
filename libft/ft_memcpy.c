/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcpy.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bemmanue <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/22 19:31:07 by bemmanue          #+#    #+#             */
/*   Updated: 2021/12/17 19:04:15 by dwillard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memcpy(void *dst, const void *src, size_t number)
{
	unsigned char		*d;
	unsigned const char	*s;

	d = dst;
	s = src;
	if (d == s)
		return (dst);
	while (number > 0)
	{
		*d++ = *s++;
		number--;
	}
	return (dst);
}
