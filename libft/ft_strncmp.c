/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strncmp.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bemmanue <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/20 16:23:50 by bemmanue          #+#    #+#             */
/*   Updated: 2021/12/22 19:37:06 by dwillard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_strncmp(const char *str1, const char *str2, size_t stop)
{
	while ((*str1 || *str2) && stop--)
		if (*str1++ != *str2++)
			return (*(str1 - 1) - *(str2 - 1));
	return (0);
}
