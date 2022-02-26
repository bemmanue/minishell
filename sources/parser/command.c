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

#include <parser.h>

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

char	**from_list_to_array(t_list *list)
{
	char	**array;
	int		index;
	t_list	*temp;

	array = malloc(sizeof(char *) * (ft_lstsize(list) + 1));
	if (!array)
		return (NULL);
	index = 0;
	temp = list;
	while (temp)
	{
		array[index++] = expand(temp->content);
		temp = temp->next;
	}
	array[index] = NULL;
	return (array);
}

char	**get_split_path(void)
{
	char	**path;
	char	*env;

	env = ft_getenv(g_info.env, "PATH");
	if (env)
	{
		path = ft_split(env, ':');
		if (!path)
			return (raise_error(MEMORY_ERROR, NULL, 1));
	}
	else
		path = NULL;
	return (path);
}

t_command	*new_command(t_list *list[2])
{
	t_command	*command;
	char		**path;

	command = malloc(sizeof(t_command));
	if (!command)
		return (raise_error(MEMORY_ERROR, NULL, 1));
	command->argv = from_list_to_array(list[0]);
	command->rdrct = from_list_to_array(list[1]);
	if (!command->argv || !command->rdrct)
		return (raise_error(MEMORY_ERROR, NULL, 1));
	path = get_split_path();
	command->name = add_full_path(ft_strdup(command->argv[0]), path);
	command->next = NULL;
	free_arr(&path);
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
