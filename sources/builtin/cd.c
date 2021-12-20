/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dwillard <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/20 21:32:16 by dwillard          #+#    #+#             */
/*   Updated: 2021/12/20 21:32:17 by dwillard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtin.h"

static int	ft_strncmp(const char *str1, const char *str2, int stop)
{
	while (stop-- && *str1++ == *str2++)
		;
	return (*str1 - *str2);
}

int	main(int argc, char **argv, char **envp)
{

}