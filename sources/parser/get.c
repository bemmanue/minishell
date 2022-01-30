
# include "parser.h"

char *get_redirect(char *str)
{
	char	*redirect;
	int		i;

	i = skip_redirect(str);
	redirect = ft_skipnchar(str, i, " \t\v");
	return (redirect);
}

char *get_argument(char *str)
{
	char	*argument;
	int		i;

	i = skip_argument(str);
	argument = strndup(str, i);
	return (argument);
}

char	*get_env(char **envp, char *var)
{
	int len;
	int	index;

	var = ft_strjoin(var, "=");
	if (!var)
		return (raise_error(MEMORY_ERROR));
	len = ft_strlen(var);
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
