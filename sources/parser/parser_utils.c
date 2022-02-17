/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bemmanue <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/15 14:00:00 by bemmanue          #+#    #+#             */
/*   Updated: 2022/02/15 14:00:00 by bemmanue         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"

void	free_strs(char *s1, char *s2, char *s3)
{
	if (s1)
		free(s1);
	if (s2)
		free(s2);
	if (s3)
		free(s3);
}

char	*insert_content(char *str, int start, int end, char *content)
{
	char	*first_part;
	char	*second_part;
	char	*temp;
	char	*new;

	first_part = strndup(str, start);
	second_part = strdup(&str[end]);
	temp = ft_strjoin(first_part, content);
	new = ft_strjoin(temp, second_part);
	if (!new)
		raise_error(MEMORY_ERROR, NULL, 1);
	free_strs(temp, first_part, second_part);
	return (new);
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

void	*raise_error(char *message, char *str, int code)
{
	char	*specify;
	char	*temp;

	g_info.error = code;
	if (str)
	{
		if (str[0] == str[1])
			temp = strndup(str, 2);
		else
			temp = strndup(str, 1);
		specify = insert_content("`'", 1, 1, temp);
		free(temp);
		message = ft_strjoin(message, specify);
		if (!message)
			raise_error(MEMORY_ERROR, NULL, 1);
	}
	ft_putendl_fd(message, 2);
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

	if (!str || !path || !access(str, F_OK) || is_builtin_command(str))
		return (str);
	index = 0;
	temp = ft_strjoin("/", str);
	while (path[index])
	{
		absolute_path = ft_strjoin(path[index], temp);
		if (!access(absolute_path, F_OK))
		{
			free(str);
			free(temp);
			return (absolute_path);
		}
		free(absolute_path);
		index++;
	}
	free(temp);
	return (str);
}
