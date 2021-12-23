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

#include "../../minishell.h"

static char	*get_str(char **envp, char *reference)
{
	char	*str;

	str = NULL;
	while (*envp)
	{
		if (!ft_strncmp(*envp, reference, ft_strlen(reference)))
		{
			str = *envp;
			break;
		}
		envp += sizeof(char *);
	}
	if (str)
	{
		str = strchr(str, '=');
		str++;
	}
	return (str);
}

int	cd(int argc, char **argv, char **envp)
{
	char	*home;

	home = get_str(envp, "HOME");
	if (!argv[0])
		chdir(home);
	return (0);
}