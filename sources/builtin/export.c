/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bemmanue <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/15 17:00:00 by bemmanue          #+#    #+#             */
/*   Updated: 2022/02/15 17:00:00 by bemmanue         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <builtin.h>

void	change_env(char *new_str, char **envp, char *name)
{
	int		index;
	char	**new;

	index = 0;
	new = malloc(sizeof(char *) * (ft_arrlen(envp) + 1));
	while (envp[index])
	{
		if (!ft_strncmp(name, envp[index], ft_strlen(name)))
			new[index] = ft_strdup(new_str);
		else
			new[index] = ft_strdup(envp[index]);
		index++;
	}
	new[index] = NULL;
	free_arr(&g_info.env);
	g_info.env = new;
}

void	add_env(char *new_str, char **envp)
{
	int		count;
	int		index;
	char	**new;

	count = ft_arrlen(envp) + 1;
	new = malloc(sizeof(char *) * (count + 1));
	index = 0;
	while (envp[index])
	{
		new[index] = ft_strdup(envp[index]);
		index++;
	}
	new[index++] = ft_strdup(new_str);
	new[index] = NULL;
	free_arr(&g_info.env);
	g_info.env = new;
}

int	ft_export(char **argv)
{
	char	*name;
	int		index;

	index = 1;
	while (argv[index])
	{
		if (ft_strchr(argv[index], '='))
		{
			name = ft_strcut(argv[index], "=");
			if (!ft_getenv(g_info.env, name))
				add_env(argv[index], g_info.env);
			else
				change_env(argv[index], g_info.env, name);
			free(name);
		}
		index++;
	}
	return (0);
}
