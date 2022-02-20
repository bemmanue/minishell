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

char	*ft_getenv(char **envp, char *name)
{
	char	*variable;
	int		len;
	int		index;

	variable = ft_strjoin(name, "=");
	if (!variable)
		return (NULL);
	len = (int)ft_strlen(variable);
	index = 0;
	while (envp && envp[index])
	{
		if (!ft_strncmp(envp[index], variable, len))
		{
			free(variable);
			return (ft_strdup(envp[index] + len));
		}
		index++;
	}
	free(variable);
	return (NULL);
}

static int	is_unset(char *name, char **argv)
{
	char	*variable;
	int		len;
	int		index;

	variable = ft_strcut(name, "=");
	len = (int)ft_strlen(variable);
	index = 1;
	while (argv[index])
	{
		if (!ft_strncmp(argv[index], variable, len))
		{
			free(variable);
			return (1);
		}
		index++;
	}
	free(variable);
	return (0);
}

char	**do_unset(char **argv, char **envp, int unset_number)
{
	char	**new;
	int		count;
	int		envp_index;
	int		new_index;

	count = ft_arrlen(envp) - unset_number;
	new = malloc(sizeof(char *) * (count + 1));
	if (!new)
		return (NULL);
	envp_index = 0;
	new_index = 0;
	while (envp[envp_index])
	{
		if (!is_unset(envp[envp_index], argv))
		{
			new[new_index] = ft_strdup(envp[envp_index]);
			new_index++;
		}
		envp_index++;
	}
	new[new_index] = NULL;
	return (new);
}

int	count_unset(char **argv, char **envp)
{
	int		count;
	int		index;
	char	*env;
	(void)envp;

	count = 0;
	index = 1;
	while (argv && argv[index])
	{
		env = ft_getenv(envp, argv[index]);
		if (env)
		{
			count++;
			free(env);
		}
		index++;
	}
	return (count);
}

int	ft_unset(char **argv, char ***envp)
{
	char	**new;
	int		unset_number;

	unset_number = count_unset(argv, *envp);
	if (unset_number)
	{
		new = do_unset(argv, *envp, unset_number);
		free_arr(envp);
		*envp = new;
	}
	return (0);
}
