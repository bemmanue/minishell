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

void	change_env(char *new, char ***envp, char *name)
{
	int		index;
	char	**temp;
	char	*name2;

	index = 0;
	temp = malloc(sizeof(char *) * (ft_arrlen(*envp) + 1));
	while ((*envp)[index])
	{
		name2 = ft_strcut((*envp)[index], "=");
		if (!ft_strncmp(name, name2, ft_strlen(name) + 1))
			temp[index] = ft_strdup(new);
		else
			temp[index] = ft_strdup((*envp)[index]);
		free(name2);
		index++;
	}
	temp[index] = NULL;
	free_arr(envp);
	*envp = temp;
}

void	add_env(char *new, char ***envp)
{
	int		count;
	int		index;
	char	**temp;

	count = ft_arrlen(*envp) + 1;
	temp = malloc(sizeof(char *) * (count + 1));
	index = 0;
	while ((*envp)[index])
	{
		temp[index] = ft_strdup((*envp)[index]);
		index++;
	}
	temp[index++] = ft_strdup(new);
	temp[index] = NULL;
	free_arr(envp);
	*envp = temp;
}

int	ft_export(char **argv, char ***envp)
{
	char	*name;
	int		index;

	index = 1;
	while (argv[index])
	{
		if (ft_strchr(argv[index], '='))
		{
			name = ft_strcut(argv[index], "=");
			if (!ft_getenv(*envp, name))
				add_env(argv[index], envp);
			else
				change_env(argv[index], envp, name);
			free(name);
		}
		index++;
	}
	return (0);
}
