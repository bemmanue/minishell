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
		str += ft_strlen(reference);
	return (str);
}

static int	relative_path(char *cdpath, char *path, char **envp)
{
	char	**pathnames;

	pathnames = ft_split(cdpath, ':');
	return (0);
}

int	cd(int argc, char **argv, char **envp)
{
	char	*home;
	char	*cdpath;

	home = get_str(envp, "HOME=");
	cdpath = get_str(envp, "CDPATH=");
	if (argc < 2)
		return (chdir(home));
	if (argc > 2)
		return (write(STDERR_FILENO, "cd: too many arguments\n", 23));
	if (argv[1][0] == '/')
		return (chdir(argv[1]));
	if (!cdpath)
		cdpath = ft_strdup(".");
	else
		cdpath = ft_strjoin(".:", cdpath);
	relative_path(cdpath, argv[1], envp);
	return (0);
}