/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_arrdup.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dwillard <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/01 18:16:55 by dwillard          #+#    #+#             */
/*   Updated: 2022/01/01 18:16:58 by dwillard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	freedom(char ***arr)
{
	char	**temp;

	temp = *arr;
	while (temp)
	{
		free(*temp);
		temp += sizeof(char *);
	}
	free(*arr);
	return (-1);
}

int	ft_arrdup(char ***arr)
{
	char	**temp;
	int		index;
	int		counter;

	index = 0;
	counter = 0;
	while (*(arr)[counter])
		counter++;
	temp = malloc(sizeof(char *) * counter + sizeof(char *));
	if (!temp)
		return (-1);
	while (index < counter)
	{
		temp[index] = ft_strdup((*arr)[index]);
		if (!temp[index])
			return (freedom(&temp));
		index++;
	}
	*arr = temp;
	return (0);
}