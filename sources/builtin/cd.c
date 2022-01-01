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

static void	change_pwd(char *path, char **envp)
{
	char	*pwd;
	char	*temp;
	int		index;

	index = 0;
	pwd = get_str(envp, "PWD=");
	while (envp[index])
	{
		if (!ft_strncmp(envp[index], "OLDPWD=", 7))
			break ;
		index++;
	}
	temp = ft_strjoin("OLDPWD=", pwd);
	if (!envp[index])
	{
		ft_strlcpy(envp[index], temp, ft_strlen(temp));
		envp[index + 1] = NULL;
	}
	else
	{
		ft_bzero(envp[index], ft_strlen(envp[index]));
		ft_strlcpy(envp[index], temp, ft_strlen(temp));
	}
	free(temp);
	ft_strlcpy(pwd, path, ft_strlen(path));
}

static int	change_dir(char *path, char **envp)
{
	if (!path)
		;
	else
		chdir(path);
	change_pwd(path, envp);
	return (0);
}

static int	relative_path(char *path, char **envp)
{
	path = ft_strjoin("./", path);
	if (!path)
		return (-1);
	change_dir(path, envp);
	free(path);
	return (0);
}

int	cd(int argc, char **argv, char **envp)
{
	char	*home;
	int		result;

	home = get_str(envp, "HOME=");
	if (argc < 2)
		result = change_dir(home, envp);
	else if (argv[1][0] == '/')
		result = change_dir(argv[1], envp);
	else
		result = relative_path(argv[1], envp);
	return (result);
}
