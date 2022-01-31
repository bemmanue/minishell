
# include "parser.h"

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
		if (strchr("<>", *list->content))
			command->rdrct[rdrct_index++] = expand(list->content);
		else
			command->argv[argv_index++] = expand(list->content);
		list = list->next;
	}
	command->argv[argv_index] = NULL;
	command->rdrct[rdrct_index] = NULL;
	command->argv[0] = add_full_path(command->argv[0], path);
	command->name = command->argv[0];
	free_array(path);
}


void	fill_command(t_command	*command, t_list *list)
{
	int		argv_number;
	int		rdrct_number;

	count_arguments(list, &argv_number, &rdrct_number);
	command->argv = malloc(sizeof(char *) * (argv_number + 1));
	command->rdrct = malloc(sizeof(char *) * (rdrct_number + 1));
	command->next = NULL;
	if (!command->argv || !command->rdrct)
		raise_error(MEMORY_ERROR, NULL);
	else
		write_command(command, list);
}

t_command	*new_command(t_list *list)
{
	t_command	*command;

	command = malloc(sizeof(t_command));
	if (!command)
		return (raise_error(MEMORY_ERROR, NULL));
	fill_command(command, list);
	return (command);
}

t_command	*get_last_command(t_command *command)
{
	t_command	*last;

	last = command;
	while (last->next)
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
