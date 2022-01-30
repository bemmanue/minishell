
# include "parser.h"

char	*expand(char *argument)
{
	char	*new;

	new = ft_strdup(argument);
//	open_dollar(&new);
//	new = strdup(open_quotes(str));
	return (new);
}

void	write_command(t_command *command, t_list *list)
{
	int		argv_index;
	int		rdrct_index;
	char	**path;

	path = ft_split(getenv("PATH"), ':');
	argv_index = 0;
	rdrct_index = 0;
	while (list)
	{
//		printf("list = %s\n", list->content);
		if (strchr("<>", *list->content))
			command->rdrct[rdrct_index++] = expand(list->content);
		else if (!command->name)
		{
			command->name = add_full_path(expand(list->content), path);
			command->argv[argv_index++] = add_full_path(expand(list->content), path);
		}
		else
			command->argv[argv_index++] = expand(list->content);
		list = list->next;
	}
	command->argv[argv_index] = NULL;
	command->rdrct[rdrct_index] = NULL;
	free_array(path);
}


void	fill_command(t_command	*command, t_list *list)
{
	int		argv_number;
	int		rdrct_number;

	count_arguments(list, &argv_number, &rdrct_number);
	command->name = NULL;
	command->argv = malloc(sizeof(char *) * (argv_number + 2));
	command->rdrct = malloc(sizeof(char *) * (rdrct_number + 1));
	command->next = NULL;
	if (!command->argv || !command->rdrct)
		raise_error(MEMORY_ERROR);
	write_command(command, list);
}

t_command	*new_command(t_list *list)
{
	t_command	*command;

	command = malloc(sizeof(t_command));
	if (!command)
		return (raise_error(MEMORY_ERROR));
	fill_command(command, list);
	return (command);
}

t_command	*get_last_command(t_command *command)
{
	t_command	*last;

	last = command;
	while (last && last->next)
		last = last->next;
	return (last);
}

void *add_new_command(t_command **command, t_list *list)
{
	t_command	*last;

	if (!*command)
		*command = new_command(list);
	else
	{
		last = get_last_command(*command);
		last->next = new_command(list);
	}
	return (NULL);
}
