/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_free_arr.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dwillard <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/25 19:30:23 by dwillard          #+#    #+#             */
/*   Updated: 2022/01/25 19:30:25 by dwillard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*free_arr(char ***arr)
{
	char	**temp;
	int		index;

	index = 0;
	temp = *arr;
	if (!temp)
		return (temp);
	while (temp[index])
	{
		free(temp[index]);
		temp[index] = NULL;
		index++;
	}
	free(temp);
	temp = NULL;
	return (NULL);
}
