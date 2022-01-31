
# include "parser.h"

char	*expand(char *argument)
{
	char	*new;

	new = ft_strdup(argument);
	if (!new)
		raise_error(MEMORY_ERROR, NULL);
	open_dollar(&new);
	open_quotes(&new);
	return (new);
}

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
}

void	free_array(char **array)
{
	int	i;

	i = 0;
	if (!array)
		return ;
	while (array[i])
		free(array[i++]);
	free(array);
}

void	*raise_error(int code, char *command)
{
	if (!g_info.error)
	{
		g_info.error = code;
		printf("minishell: ");
		if (g_info.error == PIPE_ERROR)
			printf("syntax error near unexpected token `|'\n");
		else if (g_info.error == MEMORY_ERROR)
			printf("memory could not be allocated\n");
		else if (g_info.error == PATH_ERROR)
			printf("%s: No such file or directory\n", command);
		else if (g_info.error == COMMAND_ERROR)
			printf("%s: command not found\n", command);
		else if (g_info.error == REDIRECT_ERROR)
			printf("parse error near `%s'\n", command);
		else if (g_info.error == QUOTE_ERROR)
			printf("parse error near `%s'\n", command);
	}
	free(command);
	return (NULL);
}

void	*parser_error(t_command *command)
{
	t_command	*temp;

	while (command)
	{
		temp = command;
		command = command->next;
		free_array(temp->argv);
		free_array(temp->rdrct);
		free(temp);
	}
	return (NULL);
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

char	*add_full_path(char *str, char **path)
{
	char	*absolute_path;
	int		index;
	char	*temp;

	if (!str || !access(str, F_OK) || is_builtin_command(str))
		return (str);
	if (!path)
		return (raise_error(PATH_ERROR, strdup(str)));
	index = 0;
	temp = ft_strjoin("/", str);
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
	return (raise_error(COMMAND_ERROR, strdup(str)));
//	return (str);
}
