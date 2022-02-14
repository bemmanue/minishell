/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dwillard <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/20 21:32:16 by dwillard          #+#    #+#             */
/*   Updated: 2022/01/10 19:44:00 by dwillard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <builtin.h>

static void	change_pwd(char **envp)
{
	char	**temp;
	char	*pwd;
	int		index;

	index = 0;
	pwd = getcwd(NULL, 0);
	while (envp[index] && ft_strncmp(envp[index], "PWD=", ft_strlen("PWD=")))
		index++;
	if (envp[index])
		free(envp[index]);
	else
	{
		temp = envp;
		envp = ft_arrdup(envp, 1);
		freedom(&temp);
	}
	envp[index] = ft_strjoin("PWD=", pwd);
	free(pwd);
}

static void	change_oldpwd(char **envp)
{
	char	**temp;
	char	*oldpwd;
	int		index;

	index = 0;
	oldpwd = getcwd(NULL, 0);
	while (envp[index] && ft_strncmp(envp[index], "OLDPWD=",
			ft_strlen("OLDPWD=")))
		index++;
	if (envp[index])
		free(envp[index]);
	else
	{
		temp = envp;
		envp = ft_arrdup(envp, 1);
		freedom(&temp);
	}
	envp[index] = ft_strjoin("OLDPWD=", oldpwd);
	free(oldpwd);
}

static int	change_dir(char *path, char **envp)
{
	int		check;

	change_oldpwd(envp);
	if (!path)
		check = 1;
	else
		check = chdir(path);
	change_pwd(envp);
	return (check);
}

int	ft_cd(char **argv, char **envp)
{
	char	*home;
	int		result;

	home = get_str(envp, "HOME=");
	if (!argv[1])
		result = change_dir(home, envp);
	else
		result = change_dir(argv[1], envp);
	if (result && argv)
		err_msg(argv[1]);
	return (result);
}
