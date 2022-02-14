/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strldup.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bemmanue <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/14 00:59:53 by bemmanue          #+#    #+#             */
/*   Updated: 2022/02/14 01:15:23 by bemmanue         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char    *ft_strcut(char *str, char *set)
{
    char    *new;
    int     i;

    if (!str || !set)
        return (NULL);
    i = 0;
    while (str[i] && !ft_strchr(set, str[i]))
        i++;
    new = malloc(sizeof(char) * (i + 1));
    if (!new)
        return (NULL);
    i = 0;
    while (str[i] && !ft_strchr(set, str[i]))
    {
        new[i] = str[i];
        i++;
    }
    new[i] = '\0';
    return (new);
}
