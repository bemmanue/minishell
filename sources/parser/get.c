
# include "parser.h"

char	*get_quotes_content(char *str)
{
	char	*content;
	char	quote;
	int		i;

	i = 0;
	quote = *str++;
	while (str[i] && str[i] != quote)
		i++;
	content = strndup(str, i);
	if (!content)
		raise_error(MEMORY_ERROR, NULL);
	return (content);
}

char	*get_dollar(char *str)
{
	char	*dollar;
	int		i;

	i = 1;
	if (str[i] == '?')
		dollar = ft_strdup("?");
	else
	{
		while (!strchr(" $'\"\t\v\0", str[i]))
			i++;
		dollar = strndup(&str[1], i - 1);
	}
	if (!dollar)
		raise_error(MEMORY_ERROR, NULL);
	return (dollar);
}

char *get_redirect(char *str)
{
	char	*redirect;
	int		i;

	i = skip_redirect(str);
	redirect = ft_skipnchar(str, i, " \t\v");
	if (!redirect)
		raise_error(MEMORY_ERROR, NULL);
	return (redirect);
}

char *get_argument(char *str)
{
	char	*argument;
	int		i;

	i = skip_argument(str);
	argument = strndup(str, i);
	if (!argument)
		raise_error(MEMORY_ERROR, NULL);
	return (argument);
}

//char	*get_env(char **envp, char *var)
//{
//	int len;
//	int	index;
//
//	var = ft_strjoin(var, "=");
//	if (!var)
//		return (raise_error(MEMORY_ERROR, NULL));
//	len = (int)ft_strlen(var);
//	index = 0;
//	while (envp && envp[index])
//	{
//		if (!ft_strncmp(envp[index], var, len))
//		{
//			free(var);
//			return (ft_strdup(envp[index] + len));
//		}
//		index++;
//	}
//	free(var);
//	return (ft_strdup(""));
//}
