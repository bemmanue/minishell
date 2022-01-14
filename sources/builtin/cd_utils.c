/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd_utils.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dwillard <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/14 19:44:40 by dwillard          #+#    #+#             */
/*   Updated: 2022/01/14 19:44:42 by dwillard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtin.h"

void	err_msg(char *str)
{
	ft_putstr_fd("cd: no such file or directory: ", 2);
	ft_putendl_fd(str, 2);
}

char	*get_str(char **envp, char *reference)
{
	char	*str;

	str = NULL;
	while (*envp)
	{
		if (!ft_strncmp(*envp, reference, ft_strlen(reference)))
		{
			str = *envp;
			break ;
		}
		envp += 1;
	}
	if (str)
		str += ft_strlen(reference);
	return (str);
}

void	*freedom(char ***arr)
{
	char	**temp;

	temp = *arr;
	while (temp)
	{
		free(*temp);
		temp += sizeof(char *);
	}
	free(*arr);
	return (NULL);
}
