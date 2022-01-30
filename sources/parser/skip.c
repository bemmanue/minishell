
# include "parser.h"

int	skip_argument(char *str)
{
	int	i;

	i = 0;
	while (!strchr(" <>\t\v\0", str[i]))
	{
		if (str[i] == '\'' || str[i] == '"')
			i += skip_quotes(&str[i]);
		i++;
	}
	return (i);
}

int	skip_quotes(char *str)
{
	char	quote;
	int		i;

	i = 0;
	quote = str[i++];
	while (str[i] && str[i] != quote)
		i++;
	if (str[i] == '\0')
		g_error = 1;
	return (i);
}

int	skip_redirect(char *str)
{
	char	arrow;
	int		i;

	i = 0;
	arrow = str[i++];
	if (str[i] == arrow)
		i++;
	while (strchr(" \t\v", str[i]))
		i++;
	if (!str[i] || strchr("<>", str[i]))
		g_error = 1;
	while (str[i] && !strchr(" \t\v<>", str[i]))
	{
		if (str[i] == '\'' || str[i] == '"')
			i += skip_quotes(&str[i]);
		i++;
	}
	return (i);
}
