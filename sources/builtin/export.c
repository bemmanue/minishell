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

char	**change_env(char *new_str, char **envp, char *name)
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
	return (new);
}

char	**add_env(char *new_str, char **envp)
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
	return (new);
}

int	ft_export(char **argv, char ***envp)
{
	char	**new;
	char	*name;
	int		index;
	char	*env;

	index = 1;
	while (argv[index])
	{
		if (ft_strchr(argv[index], '='))
		{
			name = ft_strcut(argv[index], "=");
			env = ft_getenv(*envp, name);
			if (!env)
				new = add_env(argv[index], *envp);
			else
			{
				new = change_env(argv[index], *envp, name);
				free(env);
			}
			free(name);
			free_arr(envp);
			*envp = new;
		}
		index++;
	}
	return (0);
}
