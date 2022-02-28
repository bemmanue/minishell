/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_isnumeric.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bemmanue <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/28 14:21:45 by bemmanue          #+#    #+#             */
/*   Updated: 2022/02/28 14:21:50 by bemmanue         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_isnumeric(char *str)
{
	int	i;

	i = 0;
	if (ft_strchr("-+", *str))
		str++;
	while (str[i])
	{
		if (!ft_isdigit(str[i]))
			return (0);
		i++;
	}
	if (i > 19 || ft_atoul(str) > 9223372036854775807)
		return (0);
	return (1);
}
