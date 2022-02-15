/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   command.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bemmanue <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/15 14:00:00 by bemmanue          #+#    #+#             */
/*   Updated: 2022/02/15 14:00:00 by bemmanue         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"

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

void	fill_command(t_command *command, t_list *list)
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
	command->name = add_full_path(ft_strdup(command->argv[0]), path);
	free_array(path);
}

t_command	*new_command(t_list *list)
{
	t_command	*command;
	int			argv_number;
	int			rdrct_number;

	command = malloc(sizeof(t_command));
	if (!command)
		return (raise_error(MEMORY_ERROR, NULL, 1));
	count_arguments(list, &argv_number, &rdrct_number);
	command->name = NULL;
	command->argv = malloc(sizeof(char *) * (argv_number + 1));
	command->rdrct = malloc(sizeof(char *) * (rdrct_number + 1));
	command->next = NULL;
	if (!command->argv || !command->rdrct)
		return (raise_error(MEMORY_ERROR, NULL, 1));
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

void	*add_new_command(t_command **command, t_list *list)
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
