
# include "parser.h"

char	*put_instead_of(char *str, int i, int j, char *env)
{
	char	*before;
	char	*temp;
	char	*new;

	before = strndup(str, i);
	temp = ft_strjoin(before, env);
	new = ft_strjoin(temp, &str[j]);
	free(before);
	free(temp);
	return (new);
}

char	*get_content(char *str)
{
	char	quote;
	int		i;

	i = 0;
	quote = *str++;
	while (str[i] && str[i] != quote)
		i++;
	str = strndup(str, i);
	return (str);
}

void	*open_quotes(char *str)
{
	char	*content;
	int		i;

	i = 0;
	while (str[i])
	{
		if (strchr("'\"", str[i]))
		{
			content = get_content(&str[i]);
			str = put_instead_of(str, i, i + 2 + ft_strlen(content), content);
			i += ft_strlen(content);
		}
		i++;
	}
	return (str);
}

char	*ft_strcon(char	*str1, char *str2, char *str3)
{
	char	*new;
	char	*temp;

	temp = ft_strjoin(str1, str2);
	new = ft_strjoin(temp, str3);
	free(temp);
	return (new);
}

char	*get_dollar(char *str)
{
	char	*dollar;
	int		i;

	i = 1;
	printf("dollar0 = %s\n", &str[0]);
	while (!strchr(" $'\"\t\v\0", str[i]))
		i++;
	dollar = strndup(&str[1], i);
	printf("dollar1 = %s\n", &str[1]);
	printf("dollar1 = %s\n", dollar);
	return (dollar);
}

void	disclose_dollar(char **str, int *i)
{
	char	*dollar;
//	char	*content;
//	char	*first_part;
//	char	*second_part;
//	char	*temp;

	dollar = get_dollar(str[*i]);
	printf("dollar2 = %s\n", str[*i]);
	(*i) += 1;
//	content = getenv(dollar);
//	printf("content = %s\n", content);
//	first_part = strndup(*str, *i);
//	second_part = strdup(str[*i + 1 + ft_strlen(dollar)]);
//	temp = ft_strcon(first_part, content, second_part);
//	free(*str);
//	*str = temp;
//	printf("$ = %s\n", *str);
//	(*i) += ft_strlen(content);
//	free(first_part);
//	free(second_part);
}

void	open_dollar(char **str)
{
	bool	double_quote;
	int		i;

	i = 0;
	double_quote = 0;
	while (str[i])
	{
		if (*str[i] == '\'' && !double_quote)
			i += skip_quotes(*&str[i]);
		else if (*str[i] == '"' && !double_quote)
			double_quote = 1;
		else if (*str[i] == '"' && double_quote)
			double_quote = 0;
		if (*str[i] == '$' && !strchr(" '\"\t\v\0", *str[i + 1]))
			disclose_dollar(str, &i);
		i++;
	}
}
