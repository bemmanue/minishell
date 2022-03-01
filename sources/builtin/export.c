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

void	*export_error(char **new)
{
	free_arr(&new);
	raise_error(MEMORY_ERROR, NULL);
	return (NULL);
}

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
		if (!new[index])
			return (export_error(new));
		index++;
	}
	new[index] = NULL;
	return (new);
}

char	**add_env(char *new_str, char **envp)
{
	int		index;
	char	**new;

	new = malloc(sizeof(char *) * (ft_arrlen(envp) + 2));
	if (!new)
		return (raise_error(MEMORY_ERROR, NULL));
	index = 0;
	while (envp[index] && !g_info.error)
	{
		new[index] = ft_strdup(envp[index]);
		if (!new[index])
			return (export_error(new));
		index++;
	}
	new[index] = ft_strdup(new_str);
	if (!new[index])
		return (export_error(new));
	new[++index] = NULL;
	return (new);
}

char	**do_export(char *argv)
{
	char	**new;
	char	*name;

	name = ft_strcut(argv, "=");
	if (!name)
		return (raise_error(MEMORY_ERROR, NULL));
	if (!ft_getenv(g_info.env, name))
		new = add_env(argv, g_info.env);
	else
		new = change_env(argv, g_info.env, name);
	free(name);
	return (new);
}

int	ft_export(char **argv)
{
	char	**new;
	int		index;

	index = 1;
	if (!argv[index])
		output_prompts();
	while (argv[index] && !g_info.error)
	{
		if (ft_strchr(argv[index], '='))
		{
			new = do_export(argv[index]);
			free_arr(&g_info.env);
			g_info.env = new;
		}
		index++;
	}
	if (g_info.error)
		return (1);
	return (0);
}
