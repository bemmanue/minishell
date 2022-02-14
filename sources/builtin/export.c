#include <builtin.h>

int	ft_arrlen(char **array)
{
	int	i;

	if (!array)
		return (0);
	i = 0;
	while (array[i])
		i++;
	return (i);
}

void	change_env(char *new, char ***envp, char *name)
{
	int		count;
	int		index;
	char	**temp;

	index = 0;
	count = ft_arrlen(*envp);
	temp = malloc(sizeof(char *) * (count + 1));
	while ((*envp)[index])
	{
		if (!ft_strncmp(name, ft_strcut((*envp)[index], "="), ft_strlen(name)))
			temp[index] = ft_strdup(new);
		else
			temp[index] = ft_strdup((*envp)[index]);
		index++;
	}
	temp[index] = NULL;
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
	*envp = temp;
}

int	ft_export(char **argv, char ***envp)
{
	char	*name;
	int		index;

	(void)envp;
	(void)argv;
	index = 1;
	while (argv[index])
	{
		if (ft_strchr(argv[index], '='))
		{
			name = ft_strcut(argv[index], "=");
			if (!getenv(name))
				add_env(argv[index], envp);
			else
				change_env(argv[index], envp, name);
		}
		index++;
	}
	return (0);
}
