
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
	    raise_error(MEMORY_ERROR, NULL, 1);
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
	    raise_error(MEMORY_ERROR, NULL,1);
	return (dollar);
}

char *get_redirect(char *str)
{
	char	*redirect;
	int		i;

	i = skip_redirect(str);
    redirect = ft_skipnchar(str, i, " \t\v");
    if (!redirect)
		raise_error(MEMORY_ERROR, NULL, 1);
	return (redirect);
}

char *get_argument(char *str)
{
	char	*argument;
	int		i;

	i = skip_argument(str);
	argument = strndup(str, i);
	if (!argument)
	    raise_error(MEMORY_ERROR, NULL, 1);
	return (argument);
}
