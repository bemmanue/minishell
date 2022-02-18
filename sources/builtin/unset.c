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

char	*ft_getenv(char **envp, char *var)
{
	int	len;
	int	index;

	var = ft_strjoin(var, "=");
	if (!var)
		return (NULL);
	len = (int)ft_strlen(var);
	index = 0;
	while (envp && envp[index])
	{
		if (!ft_strncmp(envp[index], var, len))
		{
			free(var);
			return (ft_strdup(envp[index] + len));
		}
		index++;
	}
	free(var);
	return (ft_strdup(""));
}

static int	is_unset(char **envp, char *str, char **argv)
{
	char	*env;
	int		i;

	env = ft_strcut(str, "=");
	i = 1;
	while (argv[i])
	{
		if (ft_getenv(envp, argv[i]) && !ft_strncmp(argv[i], env, ft_strlen(argv[i])))
			return (1);
		i++;
	}
	return (0);
}

static int	ft_count(char **argv, char **envp)
{
	int	count;
	int	i;

	count = 0;
	while (envp[count])
		count++;
	i = 1;
	while (argv[i])
	{
		if (ft_getenv(envp, argv[i]))
			count--;
		i++;
	}
	return (count);
}

int	ft_unset(char **argv, char ***envp)
{
	int		count;
	char	**temp;
	int		i;
	int		j;

	i = 0;
	j = 0;
	count = ft_count(argv, *envp);
	temp = malloc(sizeof(char *) * (count + 1));
	while ((*envp)[i])
	{
		if (!is_unset(*envp, (*envp)[i], argv))
			temp[j++] = (*envp)[i];
		i++;
	}
	temp[j] = NULL;
	*envp = temp;
	return (0);
}
