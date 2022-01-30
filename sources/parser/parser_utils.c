
# include "parser.h"

void	count_arguments(t_list *list, int *argv_number, int *rdrct_number)
{
	t_list	*temp;

	(*argv_number) = 0;
	(*rdrct_number) = 0;
	temp = list;
	while (temp)
	{
		if (*temp->content == '<' || *temp->content == '>')
			(*rdrct_number)++;
		else
			(*argv_number)++;
		temp = temp->next;
	}
	(*argv_number)--;
}

void	free_array(char **array)
{
	int	i;

	i = 0;
	while (array[i])
		free(array[i++]);
	free(array);
}

void	*raise_error(int code)
{
	g_error = code;
	return (NULL);
}

void	*ft_parser_error(void)
{
	if (g_error == 1)
		printf("minishell: syntax error near unexpected token `|'\n");
	if (g_error == 2)
		printf("minishell: memory could not be allocated\n");
	return (NULL);
}

char	*add_full_path(char *str, char **path)
{
	char	*absolute_path;
	int		index;
	char	*temp;

	if (!str || !access(str, F_OK) || is_builtin_command(str))
		return (str);
	if (path)
	{
		temp = ft_strjoin("/", str);
		index = 0;
		while (path[index])
		{
			absolute_path = ft_strjoin(path[index], temp);
			if (!access(absolute_path, F_OK))
			{
				free(temp);
				free(str);
				return (absolute_path);
			}
			free(absolute_path);
			index++;
		}
		free(temp);
	}
	return (str);
}

int	is_builtin_command(char *name)
{
	if (!strncmp("echo", name, ft_strlen(name)))
		return (1);
	if (!strncmp("cd", name, ft_strlen(name)))
		return (1);
	if (!strncmp("pwd", name, ft_strlen(name)))
		return (1);
	if (!strncmp("export", name, ft_strlen(name)))
		return (1);
	if (!strncmp("unset", name, ft_strlen(name)))
		return (1);
	if (!strncmp("env", name, ft_strlen(name)))
		return (1);
	if (!strncmp("exit", name, ft_strlen(name)))
		return (1);
	return (0);
}
