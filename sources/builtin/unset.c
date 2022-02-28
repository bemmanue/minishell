/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bemmanue <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/15 18:00:00 by bemmanue          #+#    #+#             */
/*   Updated: 2022/02/15 18:00:00 by bemmanue         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <builtin.h>

static int	is_unset(char *name, char *argv)
{
	char	*variable;
	int		len;

	variable = ft_strjoin(argv, "=");
	if (!variable)
	{
		raise_error(MEMORY_ERROR, NULL);
		return (-1);
	}
	len = (int)ft_strlen(variable);
	if (!ft_strncmp(name, variable, len))
	{
		free(variable);
		return (1);
	}
	free(variable);
	return (0);
}

char	**do_unset(char *argv)
{
	char	**new;
	int		envp_index;
	int		new_index;

	new = malloc(sizeof(char *) * (ft_arrlen(g_info.env)));
	if (!new)
		return (raise_error(MEMORY_ERROR, NULL));
	envp_index = 0;
	new_index = 0;
	while (g_info.env[envp_index] && !g_info.error)
	{
		if (!is_unset(g_info.env[envp_index], argv))
		{
			new[new_index] = ft_strdup(g_info.env[envp_index]);
			if (!new[new_index])
				raise_error(MEMORY_ERROR, NULL);
			new_index++;
		}
		envp_index++;
	}
	new[new_index] = NULL;
	return (new);
}

int	ft_unset(char **argv)
{
	char	**new;
	int		code;
	int		index;

	code = 0;
	index = 1;
	while (argv[index] && !g_info.error)
	{
		if (strchr(argv[index], '='))
		{
			ft_putstr_fd("bash: unset: `", STDERR_FILENO);
			ft_putstr_fd(argv[index], STDERR_FILENO);
			ft_putendl_fd("': not a valid identifier", STDERR_FILENO);
			code = 1;
		}
		else if (ft_getenv(g_info.env, argv[index]))
		{
			new = do_unset(argv[index]);
			free_arr(&g_info.env);
			g_info.env = new;
		}
		index++;
	}
	return (g_info.error);
}
