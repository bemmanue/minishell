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

void	*free_command(t_command *command)
{
	t_command	*temp;

	while (command)
	{
		temp = command;
		command = command->next;
		if (temp->name)
			free(temp->name);
		if (temp->argv)
			free_arr(&temp->argv);
		if (temp->rdrct)
			free_arr(&temp->rdrct);
		free(temp);
	}
	return (NULL);
}

void	fill_command(t_command *command, t_list *list[2])
{
	int		index;
	char	**path;
	t_list	*temp;

	path = ft_split(getenv("PATH"), ':');
	index = 0;
	temp = list[0];
	while (temp)
	{
		command->argv[index++] = expand(temp->content);
		temp = temp->next;
	}
	command->argv[index] = NULL;
	index = 0;
	temp = list[1];
	while (temp)
	{
		command->rdrct[index++] = expand(temp->content);
		temp = temp->next;
	}
	command->rdrct[index] = NULL;
	command->name = add_full_path(ft_strdup(command->argv[0]), path);
	free_arr(&path);
}

t_command	*new_command(t_list *list[2])
{
	t_command	*command;

	command = malloc(sizeof(t_command));
	if (!command)
		return (raise_error(MEMORY_ERROR, NULL, 1));
	command->name = NULL;
	command->argv = malloc(sizeof(char *) * (ft_lstsize(list[0]) + 1));
	command->rdrct = malloc(sizeof(char *) * (ft_lstsize(list[1])  + 1));
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

void	*add_new_command(t_command **command, t_list *list[2])
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
