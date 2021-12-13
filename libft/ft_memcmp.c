/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcmp.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bemmanue <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/23 16:29:45 by bemmanue          #+#    #+#             */
/*   Updated: 2021/04/23 17:19:19 by bemmanue         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_memcmp(const void *s1, const void *s2, size_t n)
{
	unsigned const char	*str1;
	unsigned const char	*str2;

	str1 = s1;
	str2 = s2;
	if (n != 0)
	{
		while (n != 0)
		{
			if (*str1 != *str2)
				return ((int)(*str1 - *str2));
			str1++;
			str2++;
			n--;
		}
	}
	return (0);
}
